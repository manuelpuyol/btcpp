### Mining process

Instead of checking for `n` 0s in the beggining of the hash, we now check for `n` 0s either at the start or end using a **regex**.

### Json/printing

Changed from a `t.to_json` method in each class to a generic `to_json(T t)` using Boost fusion, variants and visitors.
Each class that you want to convert to json must implement a `map<string, variant<...>>` with its JSON members and a `get_map` to retrieve that map.
Then, you can simply call `to_json(object)` and it should work.

### Hashing

Changed hash methods to receive the number of times they have to run. This will make the blockchain more dynamic.

### GPU

Added a GPU miner using CUDA. It only supports BTCHash (doubla sha256) and verifies only 0s at the start of the hash.
To use it make sure to add `-DUSE_CUDA=ON` to `cmake` before building.

### Benchmark

Added benchmark mode to calculate hash rate of CPU vs GPU.
To use it, make suro to add `-DBENCHMARK=ON` to `cmake` before building.