#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <vector>

/*template<class T>
class ErrorOr
{
    public:
        ErrorOr();
        virtual ~ErrorOr();

        T vlaue;
        bool error;
        string errorMessage;
    protected:
    private:
};*/


/*
 *! this function needs error checking. Crashes if 0 > index > vec.size() !
 *splits a vector into two at index.
 *The element at index is not included in any of the two new vectors.
 *The new vectors are retuned in a std::pair structure.
 */
template<class T>
std::pair<std::vector<T>,std::vector<T> > split(std::vector<T> vec, int index)
{
    std::vector<T> head;
    std::vector<T> tail;

    head.assign(vec.begin(), vec.begin()+index);
    tail.assign(vec.begin()+index+1, vec.end());

    return std::pair<std::vector<T>,std::vector<T> >(head, tail);
}

//this one does not work, which is fucking annoying since it should!
template<class T, typename iterator>
std::pair<std::vector<T>,std::vector<T> > split(std::vector<T> vec, iterator index)
{
    std::vector<T> head;
    std::vector<T> tail;

    head.assign(vec.begin(), index);
    tail.assign(++index, vec.end());

    return std::pair<std::vector<T>,std::vector<T> >(head, tail);
}

#endif // UTILS_H
