import code
import sys

#Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

def genTree(arr):
    tree = []
    tree.append(TreeNode(arr[0]))
    lastst, lasted = 0, 1
    arridx = 0
    while True:
        for idx in range(lastst, lasted):
            if tree[idx] == None: continue;
            arridx += 1
            if arridx == len(arr): break
            if arr[arridx] == None:
                tree.append(None)
            else:
                tree.append(TreeNode(arr[arridx]))
            tree[idx].left = tree[-1]
            arridx += 1
            if arridx == len(arr): break
            if arr[arridx] == None:
                tree.append(None)
            else:
                tree.append(TreeNode(arr[arridx]))
            tree[idx].right = tree[-1]
        if arridx == len(arr): break
        lastst = lasted
        lasted = len(arr)
    return tree[0]

def printTree(root):
    ret = []
    ret.append(root)
    curst, cured = 0, 1
    while curst != cured:
        for idx in range(curst, cured):
            if ret[idx] == None: continue
            ret.append(ret[idx].left)
            ret.append(ret[idx].right)
        curst = cured
        cured = len(ret)
    rett = []
    for idx in range(-1, -len(ret), -1):
        if ret[idx] != None: break
    retsize = len(ret) + idx + 1
    for idx in range(0, retsize):
        if ret[idx]: rett.append(ret[idx].val)
        else: rett.append(None)
    return rett

def genTree_uni(arr):
    tree = [None for idx in range(0, len(arr))]
    tree[0] = TreeNode(arr[0])
    for idx in range(1, len(arr)):
        far = (idx - 1) // 2
        if arr[idx] == None: continue
        tree[idx] = TreeNode(arr[idx])
        if idx % 2:
            tree[far].left = tree[idx]
        else:
            tree[far].right = tree[idx]
    return tree[0]
def printTree_uni(root):
     ret = []
     def tranvmlr(me, idx, ret):
        if not idx < len(ret):
            ret.extend(None for idx in range(len(ret), idx + 1))
        ret[idx] = me.val
        if me.left != None: tranvmlr(me.left, 2*idx + 1, ret)
        if me.right != None: tranvmlr(me.right, 2*idx + 2, ret)
     tranvmlr(root, 0, ret)
     return ret
class Solution(object):
    def deleteNode(self, root, key):
        """
        :type root: TreeNode
        :type key: int
        :rtype: TreeNode
        """
        if root == None : return None
        if root.val == key and root.left == None and root.right == None: return None
        father = None
        hit = None
        hit = root
        while hit != None and hit.val != key:
            father = hit
            if hit.val > key:
                hit = hit.left
            else:
                 hit = hit.right
        if hit == None:  return root
        if hit.left != None:
            maxleft = hit.left
            fatherl = None
            while maxleft.right != None:
                fatherl = maxleft
                maxleft = maxleft.right
            if fatherl != None:
                fatherl.right = maxleft.left
                maxleft.left = hit.left
                hit.left = maxleft
            hit.left = maxleft.left
            hit.val = maxleft.val
        elif hit.right != None:
            minright = hit.right
            fatherr = None
            while minright.left != None:
                fatherr = minright
                minright = minright.left
            if fatherr != None:
                fatherr.left = minright.right
                minright.right = hit.right
                hit.right = minright
            hit.right = minright.right
            hit.val = minright.val
        else:
            if father.left == hit: father.left = None
            else: father.right = None
        return root

if __name__ == '__main__':
    from pprint import pprint
    from functools import partial
    print = partial(pprint, compact=True)
    import yaml
    tests = yaml.load_all(open('testDeleteNode.txt'))
    s = Solution()
    for test in tests:
        for l in test:
            print(l)
        root = genTree(test[0])
        output = printTree(s.deleteNode(root, test[1]))
        print(output)
        assert output == test[2]
    #code.interact(local=locals())
    sys.exit("")
    for test in tests:
        print(test[0])
        output = printTree(genTree(test[0]))
        print(output)
        assert test[0] == output
