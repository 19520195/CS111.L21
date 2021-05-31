# Barebones
Barebones language with Interpreter & Compiler Integrated

# Notation
```
<Num>      ::= 0, 1, 2, 3, ...
<Id>       ::= Id, ID, identified, ...
<MathOper> ::= +, -, *, /
<CompOper> ::= =, !=, >, >=, <, <=
<Oper>     ::= <MathOper> | <CompOper>
<Expr>     ::= <Expr> <Oper> <Expr> | <Id> | <Num> | 
```

# `Built-in function`
| Syntax | Usage |
|-|-|
| `incr <Id>;`  | Increase value of `<Id>` by 1 unit |
| `decr <Id>;`  | Decrease value of `<Id>` by 1 unit |
| `clear <Id>;` | Set value of `<Id>` to 0 |
| `invert <Id>;` | Set value of `<Id>` to 0 if it's greater than 0, otherwise 1 |
| `assign <Id> <Expr>;` | To assign value of `<Expr>` to `<Id>` |
| `import <Id>;` | Read value of `<Id>` from input |
| `export <Id>;` | Read value of `<Id>` to output |

# `If statement`
Syntax:
```
if <Expr> then;
  # ...
[else;]
  # ...
end;
```

# `While loop`
Syntax:
```
while <Expr> do;
  # ...
end;
```
