class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError("Negative Capacity")
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return "🍪" * self.size

    def deposit(self, n):
        if self.size + n <= self.capacity:
            self._size += n
        else:
            raise ValueError("Exceed Capacity")

    def withdraw(self, n):
        if self.size - n >= 0:
            self._size -= n
        else:
            raise ValueError("There are not enough cookies")

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

def main():
    jar = Jar(15)
    print(jar.capacity)
    jar.deposit(7)
    print(str(jar))
    jar.withdraw(2)
    print(str(jar))

main()
