import random as rand


class Individual:

    value = ""
    score = 0

    def __init__(self, num_chars):
        for i in range(0, num_chars):
            rand_value = rand.randint(32, 126)
            self.value += chr(rand_value)

    """returns the string value of the individual"""
    def get_value(self):
        return str(self.value)

    """returns the score calculated by dividing the number of characters that mach the key 
    by the total number of characters"""
    def get_score(self, key):
        correct = 0
        total = len(key)
        value_list = list(self.value)
        key_list = list(key)
        for i in range(0, len(key)):
            if value_list[i] == key_list[i]:
                correct += 1
        return correct / total

    def apply_mutation(self, mutation_rate):
        value_list = list(self.value)
        for i in range(len(value_list)):
            if rand.random() <= mutation_rate:
                value_list[i] = chr(rand.randint(32, 126))
        temp = ""
        self.value = temp.join(value_list)
