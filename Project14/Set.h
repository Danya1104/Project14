#include <string>
#include <map>

class Queue {
private:
	static std::map<char, int> priority;
	std::string infix;
	std::string postfix;
	double answer;
	int check_expression(std::string);
	bool is_operation(char c);
	double execute_operation(char, std::pair<double, double>);
public:
	Queue();
	explicit Queue(std::string);
	Queue(Queue&);
	void to_postfix();
	std::string get_postfix();
	friend std::ostream& operator<<(std::ostream&, const Queue&);
	friend std::istream& operator>>(std::istream&, Queue&);
	double calculate();
	double get_result();
};
