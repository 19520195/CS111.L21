# Barebones

#
```
#BB  : is an comment line
<N>  : is a number 0, 1, 2, 3,...
<V>  : is a name of a variable.
<MO> : is a mathematic operator +, -, *, /
<CO> : is a comparison operator =, !=, >, >=, <, <=
<E>  ::= <N> | <V> | <BE>
<BE> ::= <E> (<CO> | <MO>) <E>
```

# `Built-in function`
| Syntax | Usage |
|-|-|
| `incr <V>;`  | Increase value of `<V>` by 1 unit |
| `decr <V>;`  | Decrease value of `<V>` by 1 unit |
| `clear <V>;` | Set value of `<V>` to 0 |
| `invert <V>;` | Set value of `<V>` to 0 if it's greater than 0, otherwise 1 |
| `assign <V> <E>;` | To assign value of `<E>` to `<V>` |
| `import <V>;` | Read value of `<V>` from input |
| `export <V>;` | Read value of `<V>` to output |

# `If statement`
Syntax:
```
if <Binary E> then;
  # Statement 0_0
  # Statement 0_1
  # ...
  # Statement 0_n
[else;]
  # Statement 1_0
  # Statement 1_1
  # ...
  # Statement 1_n
end;
```

# `While loop`
Syntax:
```
while <E> do;
  # Statement 0_0
  # Statement 0_1
  # ...
  # Statement 0_n
end;
```
