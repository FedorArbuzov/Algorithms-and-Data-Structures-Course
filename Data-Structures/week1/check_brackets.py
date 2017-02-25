# python3

import sys


class Bracket:
    """Bracket class.

    It stores a bracket type which is one of [, (, { and position of the
    bracket in the string.
    """

    def __init__(self, bracket_type, position):
        self.bracket_type = bracket_type
        self.position = position

    def match(self, char):
        """Matches given character with the bracket's type."""

        if self.bracket_type == '[' and char == ']':
            return True
        if self.bracket_type == '{' and char == '}':
            return True
        if self.bracket_type == '(' and char == ')':
            return True
        return False


def checker(text):

    stack = []
    for index, char in enumerate(text, start=1):

        if char in ("[", "(", "{"):
            stack.append(Bracket(char, index))

        elif char in ("]", ")", "}"):
            if not stack:
                return index

            top = stack.pop()
            if not top.match(char):
                return index
    if stack:
        top = stack.pop()
        return top.position

    return "Success"


if __name__ == "__main__":
    text = sys.stdin.read().strip("\n")
    print(checker(text))
