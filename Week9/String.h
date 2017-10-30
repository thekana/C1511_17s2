// COMP1511 17s2 -- String ADT
// Do not change this file!

#ifndef STRING_H_
#define STRING_H_

typedef struct _string *String;

// Create a new `String`, from a C-style null-terminated array of
// characters.
String newString (char *str);

// Release all resources associated with a `String`.
void destroyString (String s);

// Get the length of a `String`.
int stringLength (String s);

// Make a (mutable) copy of a `String`.
String stringClone (String s);

// Given a `String`, and an index in the `String`, return the
// character at that index.
char stringAt (String s, int index);

// Given a `String`, and a character to look for in the `String`,
// return either the index of the character, or `-1` if the character
// could not be found in the `String`.
int stringFindChar (String s, char find);

// Are two `String`s equal?
int stringsEqual (String s1, String s2);

// Given two `String`s, concatenates them into a new `String`.
String stringConcat (String s1, String s2);

#endif // !defined(STRING_H_)
