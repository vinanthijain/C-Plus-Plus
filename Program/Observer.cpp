The Observer design pattern is a behavioral design pattern that defines a one-to-many dependency between objects so that when one object (the subject) changes state, all its dependents (observers) are notified and updated automatically

class Observer
{
    public:
    virtual void update(int) = 0;
};
class Subject
{
    public:
    virtual void addObserver(shared_ptr<Observer> o)=0;
    virtual void removeObserver(shared_ptr<Observer> o)=0;
    virtual void setState(int)=0;
    virtual void notify()=0;
};
class ConcreteSubject: public Subject
{
    vector<shared_ptr<Observer> > observers;
    public:
    int state;
    void addObserver(shared_ptr<Observer> o) override
    {
        observers.push_back(o);
    }
    void removeObserver(shared_ptr<Observer> o) override
    {
        observers.erase(std::remove(observers.begin(),observers.end(),o),observers.end());
    }
    void setState(int s) override{
        this->state=s;
        notify();
    }
    void notify() override{
        for(auto& o:observers)
        {
            o->update(this->state);
        }
    }
};
class ConcreteObserver: public Observer
{
    public:
    int state;
    void update(int s) override
    {
        state=s;
        cout<<"Updated state "<<state<<endl;
    }
};
int main()
{
    shared_ptr<ConcreteSubject> s=make_shared<ConcreteSubject>();
    shared_ptr<ConcreteObserver> o1=make_shared<ConcreteObserver>();
    shared_ptr<ConcreteObserver> o2=make_shared<ConcreteObserver>();
    s->addObserver(o1);
    s->addObserver(o2);

    s->setState(10);
    s->setState(20);
}

