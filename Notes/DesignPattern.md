** SOLID principles:

Refer https://medium.com/backticks-tildes/the-s-o-l-i-d-principles-in-pictures-b34ce2f1e898 for pictorial representation

1. Single responsibility Principle.=> A class should have only one reason to change, meaning it should only have one job or responsibility.
    class Invoice {
public:
    void createInvoice() {
        // Code to create an invoice
    }
    void printInvoice() {
        // Code to print the invoice
    }
};
2. Open and Closed Principle=>Code should be open for extension and closed for modification.
class Shape {
public:
    virtual double area() const = 0;
};

class Rectangle : public Shape {
public:
    double area() const override {
        // Code to calculate the area of a rectangle
    }
};

class Circle : public Shape {
public:
    double area() const override {
        // Code to calculate the area of a circle
    }
};

3. Liskov Substitution Principle=> Objects of a superclass should be replaceable with objects of a subclass without affecting the correctness of the program. Subtypes must be substitutable for their base types.
	class Bird {
public:
    virtual void fly() = 0;
};

class Sparrow : public Bird {
public:
    void fly() override {
        // Code for sparrow flying
    }
};

class Penguin : public Bird {
public:
    void fly() override {
        // Code for penguin not flying (this violates LSP)
    }
};

4. Interface Segregation Principle=>This principle states that a client should never be forced to implement an interface that it doesn't use.
	Ex: class Machine
	{
		virtual void print();
		virtual void scan();
	},
	class Printer: public Machine
	{
		virtual void print() override
		{
			//Actual Implementation
		}
		virtual void scan() override
		{
			//Empty Implementation
		}
	}
	class Scanner: public Machine{
	virtual void print() override
		{
			//Empty Implementation
		}
		virtual void scan() override
		{
			//Actual Implementation
		}
	}
5. Dependency Inversion Principle =>This principle states that a higher level-module should not depend on a lower-level module, but they both should depend on abstractions.
class INotification {
public:
    virtual void send() = 0;
};

class EmailNotification : public INotification {
public:
    void send() override {
        // Code to send email
    }
};

class SMSNotification : public INotification {
public:
    void send() override {
        // Code to send SMS
    }
};

class NotificationService {
    INotification& notification;
public:
    NotificationService(INotification& notif) : notification(notif) {}
    void notify() {
        notification.send();
    }
};
In this example, NotificationService depends on the INotification abstraction rather than concrete implementations like EmailNotification or SMSNotification.

** Strategy Design Pattern:
The Strategy design pattern, which allows the selection of different algorithms (sorting strategies in this case) at runtime
#include<iostream>
#include<stdio.h>
#include<vector>
#include<memory>
#include<algorithm>
using namespace std;
class Strategy
{
    public:
    virtual void sortVector(vector<int>&) = 0;
    virtual ~Strategy()=default;
};
class BubbleSort:public Strategy
{
    public:
    void sortVector(vector<int> &v) override
    {
        for(int i=0;i<v.size();i++)
        {
            for(int j=i+1;j<v.size()-1;j++)
            {
                if(v[i]>v[j])
                {
                    swap(v[i],v[j]);
                }
            }
        }
    }
};
class LibSort:public Strategy
{
    public:
    void sortVector(vector<int> &v) override
    {
        sort(v.begin(),v.end());
    }
};
class Manager
{
    shared_ptr<Strategy> s;
    public:
    void setStrategy(shared_ptr<Strategy> strategy)
    {
       this->s=strategy;
    }
    void callSort(vector<int> &v)
    {
        s->sortVector(v);
    }
};
int main()
{
    unique_ptr<Manager> s;
    vector<int> v={3,1,5,7,2,9};
    s->setStrategy(make_unique<LibSort>());
    s->callSort(v);
    for(auto i:v)
        cout<<i<<endl;
}

** Chain of Responsibility:
Chain of Responsibility is a behavioral design pattern that lets you pass requests along a chain of handlers. Upon receiving a request, each handler decides either to process the request or to pass it to the next handler in the chain.

** Dependency Injection:
Dependency Injection (DI) is a design pattern in which the dependencies of a component (class or module) are provided from the outside rather than being created internally. The primary goal of dependency injection is to achieve better separation of concerns, improve testability, and promote modular, maintainable code.

In C++, dependency injection can be implemented using several techniques. Here are a few common approaches:

Constructor Injection:

The dependencies are passed to the class through its constructor.
This is a straightforward and commonly used form of dependency injection in C++.

class Logger {
public:
    Logger(LogWriter* writer) : writer(writer) {}

    void log(const std::string& message) {
        writer->write(message);
    }

private:
    LogWriter* writer;
};
Setter Injection:

Dependencies are injected through setter methods.
This allows changing dependencies after the object is constructed.

class DatabaseConnector {
public:
    void setLogger(Logger* logger) {
        this->logger = logger;
    }

void connect() {
        // Connect to the database
        if (logger) {
            logger->log("Connected to the database");
        }
    }

private:
    Logger* logger;
};
Interface Injection:

Dependencies are provided through interfaces or abstract classes.
This allows for more flexibility and easier testing by providing mock implementations.

class DataFetcher {
public:
    virtual std::string fetchData() = 0;
};

class DataProcessor {
public:
    void processData(DataFetcher* fetcher) {
        std::string data = fetcher->fetchData();
        // Process the data
    }
};
Dependency Injection Frameworks:

Some C++ frameworks and libraries provide features to manage and inject dependencies automatically.
These frameworks often use a combination of reflection and configuration files.
Example using the Boost.DI library:

#include <boost/di.hpp>

class Logger {
public:
    void log(const std::string& message) {
        std::cout << "Logging: " << message << std::endl;
    }
};

class DatabaseConnector {
public:
    void connect() {
        std::cout << "Connected to the database" << std::endl;
    }
};

class App {
public:
    App(Logger& logger, DatabaseConnector& dbConnector)
        : logger(logger), dbConnector(dbConnector) {}

    void run() {
        logger.log("Starting the application");
        dbConnector.connect();
        // Application logic
    }

private:
    Logger& logger;
    DatabaseConnector& dbConnector;
};

int main() {
    auto injector = boost::di::make_injector(
        boost::di::bind<Logger>().to<Logger>(),
        boost::di::bind<DatabaseConnector>().to<DatabaseConnector>()
    );

    auto app = injector.create<App>();
    app.run();

    return 0;
}
In this example, the Boost.DI library is used to automatically inject dependencies into the App class.

Remember that the choice of dependency injection method depends on the specific needs and requirements of your application. Manual dependency injection through constructors is a common and effective approach in C++, but if your project is large and complex, or you require more advanced features, you might explore using dependency injection frameworks or libraries.

