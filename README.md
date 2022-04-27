# Random Id Generator

Simple random alphanum generator written in standard C11.

Control the string length with `-l {len}` switch.

Compile with MSVC on Windows:

```
cl main.c /std:c11 /Fo:random-id.obj /link /OUT:random-id.exe
```

```
gcc main.c -std=c11 -o random-id
```