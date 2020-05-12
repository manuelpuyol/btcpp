## How to run

First, make sure you have the necessary dependencies installed:

```
boost@1.72.0
openssl >= 1.0.0
cmake >= 3.0.2
```

Then, at the root of the project, create a `bin` folder:

```
mkdir bin
```

Run CMake:
```
cd bin
cmake ..
```

Finally, build the project and run it (while in bin folder):
```
make
./btc++
```

## Final Project especifications

My project will consist of a **simplified** version of a Bitcoin miner (plus some blockchain structure) and a CLI to interact with it. To achieve this, Here's the structure I planned:

- Blockchain
  - has multiple blocks
  - holds the number of blocks in the chain
  - holds the number of leading 0s

- Block
  - has a header
  - has multiple transactions
  - holds the number of transactions

- Header
  - holds the nonce (used for mining)
  - holds the previous block hash
  - holds the merkle tree root (calculated from the block transactions)

- Transaction
  - holds the transaction value
  - holds the sender hash (random sha256 for now)
  - holds the receiver hash (random sha256 for now)
  - holds the transaction hash (calculated doing a sha256 of sender + receiver + value)

- Miner
  - mines (more on that later)

- CLI
  - user can create a transaction (should be stored in a file)
  - user can start the miner
  - user can dump the blockchain (should be stored in a file)
  - user can change the number of leading 0s

### Mining process

The mining process is fairly simple, the miner should follow this steps:

1. Get available transactions
2. Create a permutation of them
3. Calculate merkle root
4. Create a block header with merkle root, previous block hash, and arbitrary nonce
5. Run a double sha256
6. Check if the calculated hash has `n` leading 0s (n configured by the user)
7. If yes -> return block
8. If not and nonce not reached max -> go to step 4
9. If reached max nonce -> go to step 2

This process should be parallelized to improve performance (each thread should receive a nonce interval).