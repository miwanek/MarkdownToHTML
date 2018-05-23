 MarkdownToHTML
 ==================
 
 Simple converter from markdown to html written in c++.
 
INSTALLATION
------------

Compile both program and tests:
```
$ make
```

Compile only converter:
```
$ make release
```

Delete the compiled program:
```
$ make clean
```

USAGE
-----
To run converter type :
```
$ ./conv [arg1] [arg2] [arg3] [arg4]
``````
Where:
-  arg1 should be .md or .txt file or 'help' to display help inside the program
-  arg2 is the name of output file(without .html), if omitted "output.html" is default
-  arg3 defines the way html tags are written. Choose either "lowercase" or "uppercase". If arg3 is not given then "lowercase" is used
-  arg4 defines the type of indentation. Choose either "spaces" ( 2 spaces will be used) or "tab" (1 tab will be used then). Default is "spaces"

If more than 4 arguments are provided then input is ignored even if some of first 4 arguments were correct

To run tests type :
```
$ ./converter_tests
````
test1.md and test2.md has to be in the same directory as converter_tests

Currently working:
--------------
1) all types of headers
2) ordered and unordered lists
3) paragraphs inside and outside lists
4) horizontal rules
5) different types of links
6) all sort of emphasis
7) line breaks and spans of code


TODO:
------
+ images
+ code blocks
+ few minor improvements
