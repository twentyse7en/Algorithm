# Account Merge

This is really good problem, even if you know this can be solved with dsu, for
designing solution it may take a lot of time. I couldn't come up with solution.
SO have I have to refer to discusssion section.

## Introduction

Why is this challenging ?
<p>
Unlike other problems here the input isn't just edges or other conventional 
graph representation. Here we have a list of [name , email, email]
<br/>
what I was tring was connecting every email inside a group together and if
I see another I can join them. Another quesion if how to return the parents.
</p>

<p>
The key to solution I saw on the discussion is join the parents, not the mail.
And create a map between the mail to parent.
</p>

## Implementation
```cpp
class Solution {
public:
    int find(vector<int>& parent, int v)
    {
        if(parent[v] == v) return v;
        parent[v] = find(parent, parent[v]);
        return parent[v];
    }
    
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, int> mail_to_parent;
        vector<int> parent(accounts.size());
        
        for(int i = 0; i < accounts.size(); ++i)
            parent[i] = i;
        
        for(int i = 0; i < accounts.size(); ++i)
        {
            for(int j = 1; j < accounts[i].size(); ++j)
            {
               if(mail_to_parent.find(accounts[i][j]) == mail_to_parent.end())
                   mail_to_parent[accounts[i][j]] = i;
                else{
                   // we have already seen
                   // merge two parents
                   int a = find(parent, mail_to_parent[accounts[i][j]]);
                   int b = find(parent, parent[i]);
                    parent[b] = a;
                }
            }
        }
       
        unordered_map<int, vector<string>> umap;
        for(auto& x: mail_to_parent)
            umap[find(parent, x.second)].push_back(x.first);
        
        vector<vector<string>> res;
        for(auto&x: umap)
        {
            sort(x.second.begin(), x.second.end());
            x.second.insert(x.second.begin(), accounts[x.first][0]);
            res.push_back(x.second);
        } 
        return res;
    }
};
```

## Implementation

This is how we implement what I intially thoughtof, take away is that we can 
use `map` which helps to avoid the conversion and more simple with trade of 
space and time;

```cpp
class Solution {
    
public:
    // alway reference the map or TLE
    string find(string s, unordered_map<string, string> &umap)
    {
        if(umap[s] == s) return s;
        umap[s] = find(umap[s], umap);
        return umap[s];
    }
    
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, string> parent;
        unordered_map<string, string> group;
        
        // here values are mapped to itself as parent
        // and store it's name
        for(int i = 0; i < accounts.size(); ++i)
            for(int j = 1; j < accounts[i].size(); ++j)
            {
                parent[accounts[i][j]] = accounts[i][j];
                group[accounts[i][j]] = accounts[i][0];
            }
       
        // now we start union 
        // we make the first mail the representative
        for(int i = 0; i < accounts.size(); ++i)
        {
            // parent of the first mail
            string a = find(accounts[i][1], parent);     
            
            // make the other mail to point to the firsts parents
            for(int j = 2; j < accounts[i].size(); ++j)
            {
                parent[find(accounts[i][j], parent)] = a;
            }
        }
        
        // now start union
        // we use set as we could encounter duplicates
        unordered_map<string, set<string>> res;
        
        for(int i = 0; i < accounts.size(); ++i)
            for(int j = 1; j < accounts[i].size(); ++j)
                res[find(accounts[i][j], parent)].insert(accounts[i][j]);
        
        vector<vector<string>> s;
        // now what left is to append the name to first  
        for(auto set_mail: res){
            vector<string> buffer(set_mail.second.begin(), set_mail.second.end());
            buffer.insert(buffer.begin(), group[set_mail.first]);
            s.push_back(buffer);
        }
        return s;
    }
};
```
