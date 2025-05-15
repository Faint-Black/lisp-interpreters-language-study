# Implementation of Lisp in different languages
Implementing the same Lisp interpreter program in different programming languages to measure each codebase's development pros and cons.

Resources used:
* https://quod.lib.umich.edu/s/spobooks/bbv9810.0001.001
* https://www.lwh.jp/lisp/

## Compilation time:
Despite C being, in theory, one of the fastest languages to compile, the added tools, formatters and cmake/make build scripts heavily inflate the compilation times. Even with the -jN flag enabled on the make command coupled with the CMake cache, compilation times remain uncomfortably long.

## Development time:
In C, development times are larger than average, justified by the language's simplicity and barebones standard library. Writing multiple boilerplate utils files and having to keep track of each of them reduces development time by some amount.

## Memory management:
In C, having to keep track of what you allocated, which objects are copies or just const references, and knowing how and when to deallocate them consumes a large majority of development time.

## Portability:
In C, all the ifdefs and ifndefs make the code look ugly.

## Fun:
C is by far the most fun language to work with, the compiler barely ever complains and the finished codebase looks consistently crisp and clean, especially when coupled with the automatic style formatters.
