# QUICK NOTES

## Sentinal node

Some times we need a dummy node at start to avoid edge cases.   
For ex: remove all duplicate  `1->1->1->1` Here we need to remove
all elements and return a null pointer. For convience we add a
extra node at beginning `s->1->1->1->1` and return `s.next` as answer.
