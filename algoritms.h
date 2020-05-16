#pragma once

template<class T, class Predicate>
bool any_of(T obj, Predicate p) {
    typename T::const_iterator it = obj.begin();
    while (it != obj.end()) {
        if (p(*it))
            return true;
        ++it;
    }

    return false;
}

//template <class T, class Predicate>
//bool is_partitioned(T first,T last, Predicate pred)
//{
//    while (first != last && pred(*first)) {
//        ++first;
//    }
//    while (first != last) {
//        if (pred(*first)) return false;
//        ++first;
//    }
//    return true;
//}

template<class T, class Predicate>
bool is_partitioned(T obj, Predicate p) {
    typename T::const_iterator it = obj.begin();
    char changed = 0;
    char parted = -1;
    while (it != obj.end()) {
        bool cur = p(*it++);
        if (cur && parted == -1)
            parted = 1;
        else if (!cur && parted == -1)
            parted = 0;
        else if (!cur && !parted && changed)
            return false;
        else if (cur && parted && changed)
            return false;

        if (!changed) {
            if (cur && !parted)
                changed = 1;
            else if (!cur && parted)
                changed = 1;
        }
    }
    return true;
}



template<class T, class P, class U>
P find_not(T obj, P p, bool (*compare)(U o1, U o2)) {
    typename T::const_iterator it = obj.begin();

    while (it < obj.end() - 1) {
        if (!compare(p, *it)) {
            return *it;
        }
        ++it;
    }


}