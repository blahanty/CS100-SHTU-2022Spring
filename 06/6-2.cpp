#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Alarm;

class AlarmClock {
public:
    // Your constructors and destructor.
    AlarmClock() {
        current_hour = 0;
        current_min = 0;
        m_alarms = {};
    }

    ~AlarmClock() {
        for (auto &m_alarm: m_alarms) {
            delete m_alarm;
        }
        m_alarms.clear();
    }

    void AddAlarm(Alarm *alarm);

    void Input();

    void TimeElapse();
    // ...

private:
    std::vector<Alarm *> m_alarms;
    int current_hour, current_min;
};

class Alarm {
public:
    // Your constructors and destructor.
    Alarm(const int h, const int m, const std::string &n) {
        hour = h;
        min = m;
        name = n;
    }

    int getHour() const {
        return hour;
    }

    int getMinute() const {
        return min;
    }

    virtual void Trigger() = 0;

protected:
    // Declare protected members so that child classes have access to them.
    std::string name;
    int hour, min;
};

class RepeatableAlarm : public Alarm {
public:
    RepeatableAlarm(const int h, const int m, const std::string &n) : Alarm(h, m, n) {}

    void Trigger() override {
        std::cout << "Alarm " << name << " has triggered at ";
        if (hour < 10)
            std::cout << "0";
        std::cout << hour << ":";
        if (min < 10)
            std::cout << "0";
        std::cout << min << "." << std::endl;
    }
};

class SnoozeableAlarm : public Alarm {
public:
    SnoozeableAlarm(const int h, const int m, const std::string &n) : Alarm(h, m, n) {}

    void Trigger() override {
        std::string flag;
        std::cout << "Alarm " << name << " has triggered at ";
        if (hour < 10)
            std::cout << "0";
        std::cout << hour << ":";
        if (min < 10)
            std::cout << "0";
        std::cout << min << ". Snooze? (Y/N)" << std::endl;
        std::cin >> flag;
        if (flag == "Y") {
            min += 10;
            if (min > 59) {
                min -= 60;
                if (++hour == 24)
                    hour -= 24;
            }
        } else
            hour += 114514;
    }
};


/**************** Implementations ******************/
void AlarmClock::AddAlarm(Alarm *alarm) {
    m_alarms.push_back(alarm);
}

void AlarmClock::Input() {
    int n, hour, minute;
    char type, fuck_ccf;
    std::string name;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        Alarm *alarm;
        std::cin >> type >> hour >> fuck_ccf >> minute >> name;
        if (type == 'R')
            alarm = new RepeatableAlarm(hour, minute, name);
        else // if (type == 'S')
            alarm = new SnoozeableAlarm(hour, minute, name);
        AddAlarm(alarm);
    }
}

void AlarmClock::TimeElapse() {
    for (auto &m_alarm: m_alarms)
        if (m_alarm->getHour() == current_hour && m_alarm->getMinute() == current_min)
            m_alarm->Trigger();
    if (++current_min == 60) {
        current_min = 0;
        if (++current_hour == 24)
            current_hour = 0;
    }
}

int main() {
    AlarmClock clock;
    for (int days = 0; days < 3; days++) {
        std::cout << "Do you want to add any alarms?" << std::endl;
        clock.Input();
        for (int minute = 0; minute < 24 * 60; minute++) {
            clock.TimeElapse();
        }
        std::cout << "A day has elapsed." << std::endl;
    }
}
