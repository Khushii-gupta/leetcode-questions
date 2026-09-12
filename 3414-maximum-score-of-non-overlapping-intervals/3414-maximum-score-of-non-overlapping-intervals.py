from typing import List
from functools import lru_cache
from bisect import bisect_right
import math

class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:

        intervals = sorted(
            (l, r, w, i)
            for i, (l, r, w) in enumerate(intervals)
        )

        starts = [x[0] for x in intervals]

        @lru_cache(None)
        def dp(i, k):
            if i == len(intervals) or k == 0:
                return (0, ())

            # Don't take current interval
            skip = dp(i + 1, k)

            l, r, w, idx = intervals[i]

            # First interval whose start > r
            j = bisect_right(starts, r)

            nxt = dp(j, k - 1)

            take = (
                w + nxt[0],
                tuple(sorted((idx,) + nxt[1]))
            )

            # Maximum weight
            if take[0] > skip[0]:
                return take

            if take[0] < skip[0]:
                return skip

            # Same weight -> lexicographically smaller indices
            return min(take, skip, key=lambda x: x[1])

        return list(dp(0, 4)[1])