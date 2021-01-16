# Word Ladder

First Identify this could be solved with bfs, which I was able to 
do. Here we have to use couple of tweak as the generic bfs will give
you `TLE`.

- Way to represent: natural choice is `adj_list` but as this isn't a
a direct graph problem and contain strings we can use `unordered_set` and
some tricks. basically a neighbours is `hot` -> `hog`, `dot` they differ
by one character. For making adj_list we simply iterate through all the
words and check against all other words, which results in `O(N*N*M)`
this could be improved using hashing. `O(26*M)` to generate all
possible neighbours and check in the `unordered_set` for if we have
that possibility `O(M)`.
- In this representation, to avoid cycle remove the already visited 
word from the `unordered_set`

- Bfs will give `TLE` use bi-directional bfs to avoid bfs. This 
doesn't improve asymptotically, but could be faster in the test case.
Can be considered as pruning.

- Time complexity : `O(N*M*M*26)` O(N) = for bfs, `O(M*M*26)` for checking 
neighbour in each round of bfs.  

This is hard question, I believe it's becuase of the strict time constrain.


## Approach 1 : Normal BFS

 
```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // we don't  need to explicitly build the adj list
        // to find the neighbours we generate all possible neighbours
        // and check if it is available inside the wordList
        // for this we need a unordered_set
        
        //(O(M*N))
        unordered_set<string> words(wordList.begin(), wordList.end());
        queue<string> q;
        q.push(beginWord);
        
        
        // how does this prevent from being a cycle?
        // remove from the unordered set 
        
        int ladder = 1;
        while(q.size())
        {
            int size = q.size();
            while(size--)
            {
                string currWord = q.front(); q.pop();
                // NOTE: given endWord != beginWord
                if(currWord == endWord)
                    return ladder;
                
               // this promises we don't revisit
                words.erase(currWord);
                
                // O(M*26*M) for hashing
                // Now we try all possiblity of neighbour
                for(int i = 0; i < currWord.size(); i++)
                {
                    // saving the char to restore orginal word
                    char c = currWord[i];
                    for(int j = 0; j < 26; ++j)
                    {
                       currWord[i] = 'a' + j; 
                        if(words.find(currWord) != words.end())
                            q.push(currWord);
                    }
                    
                    // restore
                    currWord[i] = c;
                }
            }
            ladder++;
        }
        
        return 0;
    }
};
```


## Approach 2 : Bi-directional bfs

bi-directional bfs isn't hard as I thought, we have two queues, (here we used unsorted set for finding intersection)
we alternate between the shortes queue, such that we have to process only fewer nodes. I haven't deep dive into
bi-directional bfs, But I think it's worth checking out.

[resource](https://efficientcodeblog.wordpress.com/2017/12/13/bidirectional-search-two-end-bfs/)

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Now let's try bi-directional bfs, which speed up bfs
        unordered_set<string> words(wordList.begin(), wordList.end());
        
        if(words.find(endWord) == words.end())
            return 0;
       
       // utilities for bi-direction bfs
        unordered_set<string> head, tail;
        head.insert(beginWord);
        tail.insert(endWord);
        
        // there will be always two nodes, beginWord and endWord
        // actually it's counting no. of nodes, not edges
        int ladder = 2;
        while(head.size())
        {
            unordered_set<string> next;
            
            // visit all the element in the head
            for(auto neigh: head)
            {
                for(int i = 0; i < neigh.size(); ++i)
                {
                    char ch = neigh[i];
                    for(char c = 'a'; c <= 'z'; ++c)
                    {
                        // check this possiblity in the words
                        neigh[i] = c;
                        
                        // if this is available in tail list
                        // we found the intersection point
                        if(tail.find(neigh) != tail.end())
                            return ladder;
                        
                        // add if availble for next propogation 
                        if(words.find(neigh) != words.end())
                        {
                            next.insert(neigh);
                            // to avoid cycle
                            words.erase(neigh);
                        }
                    }
                    // reset the word
                    neigh[i] = ch;
                }
            }
            ladder++;
            
            // let's swap at the end to smaller one.
            if(next.size() > tail.size())
            {
                head = tail;
                tail = next;
            }
            else
            {
               head = next; 
            }
        }
        return 0;
    }
};
```
