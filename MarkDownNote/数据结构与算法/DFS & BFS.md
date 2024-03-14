> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [www.daluozha.cn](https://www.daluozha.cn/2020/06/02/DFSnBFS/)

> 举一个例子加以说明：leetcode 102 - 二叉树的层次遍历 https://leetcode-cn.com/problems/binary-tree-level-order-traversal/......

举一个例子加以说明：leetcode 102 - 二叉树的层次遍历 [https://leetcode-cn.com/problems/binary-tree-level-order-traversal/](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)

[](#深度优先搜索-Depth-First-Search "深度优先搜索 Depth First Search")深度优先搜索 Depth First Search
-----------------------------------------------------------------------------------

dfs 递归，回溯

```
var levelOrder = function(root) {
    if(!root) return []
    let result = []
    dfs(root, 0, result)
    return result
}

function dfs(node, step, result){
    if(node){
        if(!result[step]) result[step] = []
        result[step].push(node.val)
        dfs(node.left, step + 1, result)
        dfs(node.right, step + 1, result)
    }
}
```

[](#广度优先搜索-Breadth-First-Search "广度优先搜索 Breadth First Search")广度优先搜索 Breadth First Search
-----------------------------------------------------------------------------------------

bfs 维护队列

```
var levelOrder = function(root) {
    if(!root) return []
    let queue = [root], result = []
    while(queue.length){
        // 因为队列的长度是动态变化的，所以要将本层要遍历的次数先赋值出来
        let cursize = queue.length, arr = []
        while(cursize){
            let cur = queue.shift()
            arr.push(cur.val)
            cur.left && queue.push(cur.left)
            cur.right && queue.push(cur.right)
            cursize--
        }
        result.push(arr)
    }
    return result
};
```