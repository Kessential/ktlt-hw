import random

with open("test.txt", "w", encoding="utf-8") as f:
    for i in range(1, 1000000):
        f.write(f"{random.randint(1, 1000000)}\n")
