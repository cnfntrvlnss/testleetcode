testtxt = '''
- [1, 2]
- [3, 4]
- 2.5
...
---
- [3, 5, 6, 9]
- [1, 2, 4, 7, 8, 10, 11, 12]
- 6.5
...
---
- [3,]
- [1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12]
- 6.5
...
---
- [1, 3]
- [2,]
- 2
...
---
- [1, 3, 5, 7, 9]
- [2, 4, 6, 8, 10, 11, 12]
- 6.5
'''

import operator
class Solution(object):
    def findMthSortedArrays(self, smallee, largee, mth, lt):
        """
        TODO not apply for mth is bigger than  size of any list.
        :type smallee: List[int]
        :type largee: List[int]
        :rtype: float
        """
        assert len(largee) >= len(smallee), "largee should be larger than smallee"
        assert mth < len(largee), "mth %d should be less than size of larger list %d" % (mth, len(largee))
        st = 0
        if len(smallee) == 0:
            return largee[mth]
        if lt(largee[mth] , smallee[0]):
            return largee[mth]
        if mth >= len(smallee): ed = len(smallee) - 1
        else: ed = mth - 1
        if not lt(largee[mth - ed - 1] , smallee[ed]):
            if ed < len(smallee) -1 and lt(smallee[ed + 1] , largee[mth - ed -1]):
                return smallee[ed + 1]
            else:
                return largee[mth - ed - 1]
        if ed == 0:
            return smallee[ed]

        while True:
            md = (st + ed) // 2
            if not lt(largee[mth -md -1] , smallee[md]) and not lt( smallee[md], largee[mth -md -1]): break;
            if st + 1 == ed: break
            if lt(largee[mth - md - 1] , smallee[md]):
                ed = md
            else:
                st = md
        if not lt(largee[mth - md - 1] , smallee[md]):
            if lt(smallee[md+1] , largee[mth - md -1]):
                return smallee[md+1]
            else:
                return largee[mth -md -1]
        else:
            if lt(largee[mth -md] , smallee[md]): return largee[mth - md]
            else: return smallee[md]

    def findMedianSortedArrays(self, nums1, nums2):
        class reverselist(object):
            def __init__(self, li):
                self.li = li

            def __len__(self):
                return len(self.li)

            def __getitem__(self, item):
                return self.li[-item - 1]

        if len(nums1) > len(nums2):
            nums2, nums1 = nums1, nums2
        med = (len(nums1) + len(nums2)) // 2
        if med < len(nums2):
            val1 = self.findMthSortedArrays((nums1), nums2, med, operator.lt)
        else:
            val1 = self.findMthSortedArrays(reverselist(nums1), reverselist(nums2), med - 1, operator.gt)
        if med * 2 == len(nums1) + len(nums2):
            return (val1 + self.findMthSortedArrays(nums1, nums2, med - 1, operator.lt)) / 2
        else:
            return val1

if __name__ == '__main__':
    s = Solution()
    import yaml
    tests = yaml.load_all(testtxt)
    for t in tests:
        median = s.findMedianSortedArrays(t[0], t[1])
        assert median == t[2], "%s\n%s" % (str(t), median)