# meow lang

[usage](#usage) [language](#language) [todo](#todo)
small compilator for a toy language. it will compile to C, but eventually i want it compiling to mashine code

# usage

> [!TIP]
> uncomment `printTokens(tokens, filename);` in `main.cc` to see how the lexer works

1. compile compilator

    ```sh
    make
    ```

2. use it on `example`

    ```sh
    ./bin/meow example
    ```


# language

example:
```
# meowlang
let s = "meow";
print "Hello " s "!";

let x = 10;
if x == 10 then
    y = 5;
end

while y > 0 then
    y = y - 1;
end
```

# todo

done:
- lexer
    - tokenizing
    - unclosed strings
    - unrecognised characters
    - small error handling

not done :3
- parser
- emmiter