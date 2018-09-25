/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
private:
    int search_in_range(vector<Interval>& intervals, int left, int right, int val) {
        if (left >= right) {
            return left;
        }
        int mid = (left+right+1)/2;
        if (val > intervals[mid].start) {
            return search_in_range(intervals, mid, right, val);
        }
        if (val < intervals[mid].start) {
            return search_in_range(intervals, left, mid-1, val);
        }
        return mid;
    }
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> result;
        if (intervals.size() == 0) {
            result.push_back(newInterval);
        }
        int left_idx = search_in_range(intervals, 0, intervals.size()-1, newInterval.start);
        int right_idx = search_in_range(intervals, 0, intervals.size()-1, newInterval.end);
        for (int i=0; i<intervals.size(); i++) {
            if (i < left_idx || i > right_idx) {
                result.push_back(intervals[i]);
                continue;
            }
            if (i == left_idx) {
                if (left_idx == right_idx) {
                    Interval tmp(intervals[i].start, intervals[i].end);
                    if (newInterval.start > intervals[i].end) {
                        tmp.start = newInterval.start;
                        tmp.end = newInterval.end;
                        result.push_back(intervals[i]);
                        result.push_back(tmp);
                        continue;
                    }
                    if (newInterval.end < intervals[i].start) {
                        tmp.start = newInterval.start;
                        tmp.end = newInterval.end;
                        result.push_back(tmp);
                        result.push_back(intervals[i]);
                        continue;
                    }
                    if (newInterval.start < intervals[i].start) {
                        tmp.start = newInterval.start;
                    }
                    if (newInterval.end > intervals[i].end) {
                        tmp.end = newInterval.end;
                    }
                    result.push_back(tmp);
                } else {
                    if (newInterval.start > intervals[left_idx].end && newInterval.end < intervals[right_idx].start) {
                        result.push_back(intervals[left_idx]);
                        result.push_back(newInterval);
                        result.push_back(intervals[right_idx]);
                    } else if (newInterval.start > intervals[left_idx].end) {
                        intervals[right_idx].start = newInterval.start;
                        if (newInterval.end > intervals[right_idx].end) {
                            intervals[right_idx].end = newInterval.end;
                        }
                        result.push_back(intervals[left_idx]);
                        result.push_back(intervals[right_idx]);
                    } else if (newInterval.end < intervals[right_idx].start) {
                        intervals[left_idx].end = newInterval.end;
                        if (newInterval.start < intervals[left_idx].start) {
                            intervals[left_idx].start = newInterval.start;
                        }
                        result.push_back(intervals[left_idx]);
                        result.push_back(intervals[right_idx]);
                    } else {
                        Interval tmp;
                        if (newInterval.start < intervals[left_idx].start) {
                            tmp.start = newInterval.start;
                        } else {
                            tmp.start = intervals[left_idx].start;
                        }
                        if (newInterval.end > intervals[right_idx].end) {
                            tmp.end = newInterval.end;
                        } else {
                            tmp.end = intervals[right_idx].end;
                        }
                        result.push_back(tmp);
                    }
                    i = right_idx;
                }
            }
        }
        return result;
    }
};
