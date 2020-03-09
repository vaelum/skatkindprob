# Skat Kind Probabilities

Computational proof calculating the probabilites for 0 to 8 three of a kind in a game of Skat. For further information on Skat take a look at https://en.wikipedia.org/wiki/Skat_(card_game).

## Build & Run

To build this repository you need:
* cmake and a c++ compiler with support for c++17 and std:atomic
* gmp library (https://gmplib.org)

The following commands are for linux like operating systems.
If you are using something else you still should be able to build this project
but possibly will need other commands.

```
git clone git@github.com:inversitas/skatkindprob.git
cd skatkindprob
mkdir build
cd build
cmake ..
make
./skb --help
```


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details


