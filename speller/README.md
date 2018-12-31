# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Pneumonoultramicroscopicsilicovolcanoconiosis is an invented very long word that is a lung disease caused by inhaling very fine ash and sand dust. It's important to note that it is 45 letters long since that will be the maximum allowed length of a word, denoted by `LENGTH`.

## According to its man page, what does `getrusage` do?

`getrusage` is a method that returns "resource usage measures" for the first argument that's passed when calling the method, and will store those statistics in the struct provided as the second argument.

In `speller.c`, `getrusage`'s first argument is `RUSAGE_SELF`, which means `getrusage` will return resource statistics for the resources used by all threads in the process.

`getrusage` stores statistics it returns like user CPU time used, system CPU time used, etc. into the struct pointed to by the second argument. If some of the fields in the struct are not given specific values, they are 0 be default.

## Per that same man page, how many members are in a variable of type `struct rusage`?

In a variable of type `struct rusage`, there are 16 members.

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Passing variables to another method requires copying the variables and then handing the copies to the other method. For relatively small data types like integers and booleans this isn't too much of a problem, but the structs `before` and `after` are quite big. Copying the structs to pass them into this other method is inefficient since pointers to the structs could be given instead. Moreover, since we're not changing the contents of the structs, pointers to the structs would provide the same information.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The text is loaded from the .txt file specified in the second commandline argument using a file pointer.

`word` is implmented similarly to a stack, with `index` representing the top of the stack, and is also the length of `word`.

The `for` loop starts with the initialization of an integer `c` which is the first character of the .txt file. The `for` loop iterates over the characters in the file, and will stop when it reaches the end of the file.

The very first if statement checks if `c` is an alphabetical letter or an apostrophe and if `index` is greater than 0. `index` being greater than 0 means that there are other letters in `word`. If true, `c` is inserted into `word` at `index` and index is incremented by 1 (Note how this is similar to pushing to a stack). The if statement on lines 81 - 88 checks if `index` is greater than `LENGTH`, which means that the word is longer than 45 characters. The `while` statement that is executed if `index` is greater than `LENGTH` moves`c` along the file until it reaches a non-alphabetic character (like a space) or the end of the file. `index` is then set to 0 for the next word in the file.

If the expression in the first `if` is false, the `else if` is activated, which checks if `c` is a digit. For this `else if` to be activated, `c` is not an alophabetical letter or an apostrophe. If `c` is indeed a digit, the `while` statement that is then executed moves `c` along the file until it reaches a non-alphabetic character (like a space) or the end of the file. `index` is then set to 0 for the next word in the file.

If the expression in the first `else if` is false, the final `else if` is activated, which checks if `index` is greater than 0 - if a word has already been constructed. For this final `else if` to be activated, `c` is not an alphabetical letter, an apostrophe, or a digit. `word` is terminated by entring `\0` at `index`, and the number of words is increased by 1. Now that `word` is a complete word, it is passed to `check` which checks if it is in the dictionary. Wrapped around this method call are `getrusage`s, which are used to calculate how long `check` takes to execute. If the word has been missepelled, the word is printed to terminal and the number of misspellings incremented by 1.

Finally, `index` is set to 0 to prepare for the next word.
## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

As great as strings are, they don't have a way to discern between a word and a jumble of characters. Both may seem identical, but special characters, spaces, and other characters that are not alphabtic letters could be mistaken as part of a word. Reading each word's characters one at a time allows us to ensure that each character is an alphabetical letter and that just a single word is put into `word`.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

They should be declared as `const`s so that `check` and `load` don't change their values. If they weren't declared as `const`s and `check` or `load` changed the value of the pointer passed in, the pointer would point to something other than `word` or `dictionary`, effectively losing `word` and `dictionary` to garbage values.