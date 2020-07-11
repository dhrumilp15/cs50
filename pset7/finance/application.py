import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
import time

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = db.execute("SELECT Symbol, Shares, Price, Total FROM portfolio WHERE id = :id", id = session['user_id'])

    cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session['user_id'])[0]['cash']

    allcash = cash

    symbol, shares, price, total = [], [], [], []

    for port in portfolio:
        symbol.append(port['Symbol'])
        shares.append(port['Shares'])
        price.append(port['Price'])
        total.append(port['Total'])
        allcash += port['Total']

    return render_template("/index.html", symbol = symbol, shares = shares, price = price, total = total, cash = cash, allcash = allcash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("stock"):
            return apology("Grand Baguette! Enter the stock!")

        if not request.form.get("shares") and request.form.get("shares") > 0:
            return apology("Grand Baguette! Enter the number of shares!")

        stock = lookup(request.form.get("stock"))
        shares = int(request.form.get("shares"))


        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])[0]['cash']

        if cash > stock['price'] * shares:
            db.execute("INSERT INTO History (id, Symbol, Shares, Price, Time) VALUES (:id, :symbol, :shares, :price, :time)", id = session["user_id"], symbol = stock['symbol'], shares = shares, price = stock['price'], time = time.strftime("%y-%m-%d %H:%M:%S"))

            db.execute("UPDATE users SET cash = cash - :amount WHERE id = :id", amount = stock['price'] * shares, id = session["user_id"])

            res = db.execute("SELECT * FROM portfolio WHERE id = :id AND Symbol = :symbol", id = session["user_id"], symbol = stock['symbol'])

            if not res:
                db.execute("INSERT INTO portfolio (id, Symbol, Shares, Price, Total) VALUES (:id, :symbol, :shares, :price, :total)", id = session["user_id"], symbol = stock['symbol'], shares = shares, price = stock['price'], total = shares * stock['price'])
            else:
                db.execute("UPDATE portfolio SET shares = shares + :shares AND total = total + :total WHERE id = :id", shares = shares, total = shares * stock['price'], id = session["user_id"],)

        else:
            return apology("Grand Baguette! Insufficient Funds!")

        return redirect("/")

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT Symbol, Shares, Price, Time FROM History WHERE id = :id", id = session["user_id"])
    return render_template("history.html", history = history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        if not request.form.get("stock"):
            return apology("Grand Baguette! You have to write the ticker symbol!")

        ticker = lookup(request.form.get("stock"))

        if ticker:
            return render_template("quotes_show.html", name = ticker["name"], price = ticker["price"], symbol = ticker["symbol"])
        else:
            return apology("Grand Baguette! The ticker symbol doesn't exist!")

    else:
        return render_template("quote.html")
    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("Grand Baguette! Missing Username")

        elif not request.form.get("password"):
            return apology("Grand Baguette! Missing Password", 403)

        elif not request.form.get("password_conf"):
            return apology("Grand Baguette! Missing Password Confirmation!", 403)

        elif not request.form.get("password") == request.form.get("password_conf"):
            return apology("Grand Baguette! Passwords don't match!", 403)

        userboi = request.form.get("username")
        hashboi = generate_password_hash(request.form.get("password"))

        res = db.execute("INSERT into users (username, hash) VALUES(:username, :hashman)", username = userboi, hashman = hashboi)
        if not res:
            return apology("Grand Baguette! Someone has stolen that username!", 409)

        user_id = db.execute("SELECT id FROM users WHERE username = (:username)", username = userboi)[0]["id"]
        session["user_id"] = user_id
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        if not request.form.get("stock"):
            return apology("Grand Baguette! Enter a stock name!")

        if not int(request.form.get("shares")):
            return apology("Grand Baguette! Enter an integer number of shares!")

        symbol = request.form.get("stock")
        shares = int(request.form.get("shares"))

        price = lookup(symbol)['price']
        sold = price * shares

        existingstocks = db.execute("SELECT Symbol FROM portfolio WHERE id = :id", id = session["user_id"])

        stocklist = []

        for stocks in existingstocks:
            stocklist.append(stocks['Symbol'])

        if symbol not in stocklist:
            return apology("Grand Baguette! You can't sell that stock since you don't own it!")

        existingshares = db.execute("SELECT Shares FROM portfolio WHERE Symbol = :symbol", symbol = symbol)[0]['Shares']
        if existingshares - shares == 0:
            db.execute("DELETE FROM portfolio WHERE Symbol = :symbol", symbol = symbol)
        else:
            db.execute("UPDATE portfolio SET Shares = Shares - :shares WHERE Symbol = :symbol", shares = shares, symbol = symbol)
            db.execute("UPDATE portfolio SET Total = Total - :sold WHERE Symbol = :symbol", sold = sold, symbol = symbol)

        db.execute("INSERT INTO History (id, Symbol, Shares, Price, Time) VALUES (:id, :symbol, :shares, :price, :time)", id = session["user_id"], symbol = symbol, shares = -1 * shares, price = price, time = time.strftime("%y-%m-%d %H:%M:%S"))

        db.execute("UPDATE users SET cash = cash - :sold", sold = sold)

        return redirect("/")
    else:
        return render_template("sell.html")

@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change a user's password"""
    if request.method == "POST":

        if not request.form.get("pass") or not request.form.get("confirmpass"):
            return apology("Grand Baguette! Enter in your passwords!")

        if not request.form.get("pass") == request.form.get("confirmpass"):
            return apology("Grand Baguette! Passwords don't match!")

        hashpass = generate_password_hash(request.form.get("pass"))

        db.execute("UPDATE users SET hash = :hash", hash = hashpass)

        return redirect("/")
    else:
        return render_template("password.html")



def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
