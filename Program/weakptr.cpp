#include <iostream>
#include <memory>

int main() {
    // Create a shared pointer
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(42);

    // Create a weak pointer from the shared pointer
    std::weak_ptr<int> weakPtr = sharedPtr;

    // Use the weak pointer
    if (auto lockedPtr = weakPtr.lock()) {
        std::cout << "Weak pointer value: " << *lockedPtr << std::endl;
    } else {
        std::cout << "Weak pointer is expired." << std::endl;
    }

    // The shared pointer still exists, so the weak pointer is not expired
    if (auto lockedPtr = weakPtr.lock()) {
        std::cout << "Weak pointer value after shared pointer still exists: " << *lockedPtr << std::endl;
    } else {
        std::cout << "Weak pointer is expired." << std::endl;
    }

    // Reset the shared pointer
    sharedPtr.reset();

    // Attempt to use the weak pointer after the shared pointer is reset
    if (auto lockedPtr = weakPtr.lock()) {
        std::cout << "Weak pointer value after shared pointer is reset: " << *lockedPtr << std::endl;
    } else {
        std::cout << "Weak pointer is expired after shared pointer is reset." << std::endl;
    }

    return 0;
}

