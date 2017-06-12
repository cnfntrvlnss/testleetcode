import code


class Solution(object):
    def poorPigs(self, buckets, minutesToDie, minutesToTest):
        circle = minutesToTest // minutesToDie + 1
        for idx in range(1, 100):
            if (circle ** idx) >= buckets:
                return idx
    def poorPigs0(self, buckets, minutesToDie, minutesToTest):
        circle = minutesToTest // minutesToDie
        for idx in range(1, 100):
            if (idx+1) ** circle >= buckets:
                return idx

    def poorPigs1(self, buckets, minutesToDie, minutesToTest):
        """
        :type buckets: int
        :type minutesToDie: int
        :type minutesToTest: int
        :rtype: int
        """
        def getceil(buckets, circle):
            ceilnum = buckets // circle
            if buckets % circle:
                ceilnum += 1
            return ceilnum
        circle = minutesToTest // minutesToDie
        resarr = []
        fparr = []
        for idx in range(1, circle+1):
            resarr.append([getceil(bucket, idx) for bucket in range(1, buckets+1)])
            fparr.append([0 for i in range(0, buckets)])
        if circle < 2:  return resarr[circle-1][buckets-1]
        if buckets <= circle: return 1
        for idx in range(1, circle):
            for jdx in range(idx+1, buckets):
                for kdx in range(idx, jdx):
                    if (kdx+1) * resarr[idx-1][kdx] >= jdx + 1:
                        if resarr[idx-1][kdx] +1 < resarr[idx][jdx]:
                            resarr[idx][jdx] = resarr[idx-1][kdx] + 1
                            fparr[idx][jdx] = kdx
                        anoch = getceil(jdx+1,  kdx)
                        if anoch < resarr[idx][jdx]:
                            resarr[idx][jdx] = anoch
                            fparr[idx][jdx] = kdx -1
                        break

        if buckets == 17: code.interact(local= locals())
        return resarr[circle-1][buckets-1]

if __name__ == '__main__':
    resarr1 = list(range(0, 10))
    resarr2 = list(range(0, 10))
    for circle in range(1, 5):
        for pig in range(1, 10):
            resarr1[pig - 1] = (circle + 1) ** pig
            resarr2[pig - 1] = (pig + 1) ** circle
        print(resarr1, resarr2)
        print('')
    s = Solution()
    print(s.poorPigs(81, 1, 5))
    print(s.poorPigs0(81, 1, 5))


