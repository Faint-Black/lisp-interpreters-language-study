# Implementation of Lisp in different languages
Implementing the same Lisp interpreter program in different programming languages to measure each codebase's development pros and cons.

The https://www.lwh.jp/lisp/ online guide will be used as a basis for the general Lisp design.

Further resources:

* Algorithm Composition: A Gentle Instroduction to Music Composition Using Common Lisp and Common Music.

## Compilation time:
Despite C being, in theory, one of the fastest languages to compile, the added tools, formatters and cmake/make build scripts heavily inflate the compilation times. Even with the -jN flag enabled on the make command coupled with the CMake cache, compilation times remain uncomfortably long.

## Development time:
In C, development times are larger than average, justified by the language's simplicity and barebones standard library. Writing multiple boilerplate utils files and having to keep track of each of them reduces development time by some amount.

## Memory management:
In C, having to keep track of what you allocated, which objects are copies or just const references, and knowing how and when to deallocate them consumes a large majority of development time.
