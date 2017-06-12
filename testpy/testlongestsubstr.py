testtxt = '''
- abcabcbb
- abc
...
---
- bbbbb
- b
...
---
- pwwkew
- wke
...
---
- ohomm
- hom
'''
class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        mChs = {}
        mChs[s[0]] = 0
        maxchslen = 1
        for idx in range(1, len(s)):
            if s[idx] in mChs:
                if len(mChs) > maxchslen: maxchslen = len(mChs)
                stidx = idx - len(mChs)
                for jdx in range(stidx, mChs[s[idx]] + 1):
                    mChs.pop(s[jdx])

            mChs[s[idx]] = idx

        if len(mChs) > maxchslen: maxchslen = len(mChs)
        return maxchslen

if __name__ == '__main__':
    import yaml
    tests = yaml.load_all(testtxt)
    s = Solution()
    for t in tests:
        t1 = s.lengthOfLongestSubstring(t[0])
        assert t1 == len(t[1]), "%d %s" %(t1, t[1])
