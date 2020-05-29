### Mining process

Instead of checking for `n` 0s in the beggining of the hash, we now check for `n` 0s either at the start or end using a **regex**.

### Json/printing

Changed from a `t.to_json` method in each class to a generic `to_json(T t)` using Boost fusion, variants and visitors.
Each class that you want to convert to json must implement a `map<string, variant<...>>` with its JSON members and a `get_map` to retrieve that map.
Then, you can simply call `to_json(object)` and it should work.

### Hashing

Changed hash methods to receive the number of times they have to run. This will make the blockchain more dynamic.