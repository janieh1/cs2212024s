/**
 * @file quack.cpp
 * Implementation of the Quack class.
 *
 */

template <class T>
Quack<T>::Quack() {
    /**
     * @todo Your code here!
     */
    n1 = 0;
    n2 = 0;
    //data.resize(1, T());
}

/**
 * Adds the parameter object to the right of the Quack.
 *
 * @param newItem object to be added to the Quack.
 */
template <class T>
void Quack<T>::push_right(T newItem) {
    /**
     * @todo Your code here!
     */
    //std::cout << "vector push back: " << std::to_string(newItem) << std::endl;
    if (n2 == data.size()) {
        data.push_back(newItem);
    } else {
        data[n2] = newItem;
    }
    n2++; 
}

/**
 * Removes the object at the left of the Quack, and returns it to the
 * caller.
 *
 * See .h file for implementation notes.
 *
 * @return The item that used to be at the left of the Quack.
 */
template <class T>
T Quack<T>::pop_left() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    // remove at index n1 and inc it - data now starts at index (n1 + 1)
    T toRemove = peekL();
    data[n1] = T();
    n1++;
    //n2--;
    if (n1 >= n2 - n1) {
        for (int i = n1; i < n2; i++) {
            data[i - n1] = data[i];
        }
    data.resize(n2 - n1);
    n1 = 0;
    n2 = data.size();
    }
    return toRemove;
}
/**
 * Removes the object at the right of the Quack, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Quack.
 */
template <class T>
T Quack<T>::pop_right() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */

    T toRemove = peekR();
    //data.erase(data.begin() + n1 + n2 - 1);
    data[n1 + n2 - 1] = T();
    //data.erase(data.back());

    n2--;
    if (n1 >= n2 - n1) {
        for (int i = n1; i < n2; i++) {
            data[i - n1] = data[i];
        }
    data.resize(n2 - n1);
    n1 = 0;
    n2 = data.size();
    }
    return toRemove;
}

/**
 * Finds the object at the left of the Quack, and returns it to the
 * caller. Unlike pop_left(), this operation does not alter the quack.
 *
 * @return The item at the front of the quack.
 */
template <class T>
T Quack<T>::peekL() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return data[n1];
}

/**
 * Finds the object at the right of the Quack, and returns it to the
 * caller. Unlike pop_right(), this operation does not alter the quack.
 *
 * @return the value of The item at the right of the quack.
 */
template <class T>
T Quack<T>::peekR() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return data[n2 - 1];
}

/**
 * Determines if the Quack is empty.
 *
 * @return bool which is true if the Quack is empty, false otherwise.
 */
template <class T>
bool Quack<T>::is_empty() const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return (n2 == 0);
}
