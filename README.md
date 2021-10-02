# TTGen

A truth table generator.

<p align="center">
  <img src="https://user-images.githubusercontent.com/33803413/135724542-aef22eff-f7fb-4008-a8ce-69732d65e634.png" />
</p>

## Building

```
cmake . -Bbuild
cmake --build build
```

## Testing

To build unit tests, turn on the `BUILD_TESTING` option:
```
cmake . -Bbuild -DBUILD_TESTING=ON
```

## Usage

`ttgen` reads logical expressions from `stdin` and writes corresponding truth tables to `stdout` until `EOF`. Tokens in the input expressions are case-sensitive. All logical operators should be uppercased. To generate a truth table with more than one expression, enter these expressions on a single line, separating them with `;`. Parentheses can be used to override the default evaluation. Empty input lines are ignored. Multiple whitespace characters are treated as a single one. Leading and trailing whitespaces have no effect.

### Operators

Operator | Precedence | Arity | Associativity
--- | --- | --- | ---
NOT | 1 | 1 | right-to-left
AND | 2 | 2 | left-to-right
OR | 3 | 2 | left-to-right
XOR | 4 | 2 | left-to-right
IMPLY | 5 | 2 | right-to-left

## License

[MIT](https://github.com/wadiim/ttgen/blob/master/LICENSE)
