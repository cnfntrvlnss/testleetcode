# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

def reverselist(li):
    prev = None
    cur = li
    while cur != None:
        ncur = cur.next
        cur.next = prev
        prev = cur
        cur = ncur
    return prev

def genlist(num):
    ret = ListNode(num %10)
    cur = ret
    powi = 2
    while True:
        simple1 = int(10 ** (powi - 1))
        simple2 = int(10 ** (powi))
        if not num // simple1:
            break
        cur.next = ListNode((num % simple2) // simple1)
        cur = cur.next
        powi += 1
    return reverselist(ret)

def parselist(li):
    li = reverselist(li)
    num = 0
    cur = li
    powi = 0
    while cur != None:
        num += cur.val * (10 **powi)
        powi += 1
        cur = cur.next
    reverselist(li)
    return int(num)

class Solution(object):
    def addTwoNumbers(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        def addTo(li, retl):
            upnum = li.val
            while True:
                retl.val += upnum
                upnum = retl.val // 10
                retl.val %= 10
                if upnum == 0: break
                if retl.next == None: retl.next = ListNode(0)
                retl = retl.next

        def addToList(l1, retl):
            cur1 = l1
            cur = retl
            while True:
                addTo(cur1, cur)
                cur1 = cur1.next
                if cur1 == None: break
                if cur.next == None: cur.next = ListNode(0)
                cur = cur.next

        l1 = reverselist(l1)
        l2 = reverselist(l2)
        retl = ListNode(0)

        addToList(l1, retl)
        addToList(l2, retl)
        reverselist(l1)
        reverselist(l2)
        return reverselist(retl)

if __name__ == '__main__':
    import yaml
    #num = parselist(genlist(23452000))
    #print(num)
    num1 = 99
    num2 = 9
    l1 = genlist(num1)
    l2 = genlist(num2)
    s = Solution()
    retl = s.addTwoNumbers(l1, l2)
    assert parselist(retl) == num1 + num2, (parselist(retl), num1 + num2)