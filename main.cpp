#include <iostream>
#include <cstdlib>  
#include <ctime>     


using namespace std;

enum EN_QUESTIONS_LEVEL{EASY=1,MID,HARD,LVL_MIX,LVL_NOT_KNOWN};
string questions_level_text[5] = { "","Easy","Mid","Hard","Mix" };

enum EN_QUESTIONS_TYPE{ADD=1,SUB,MUL,DIV,QT_MIX,NOT_KNOWN};
string question_type_text[6] = { "","Add","Sub","Mul","Div","Mix" };

enum EN_QUESTION_RESULT{WRONG=0,CORRECT,QUESTION_RESULT_NOT_KNOWN};
string question_result_text[2] = { "Wrong","Correct"};
string question_result_message_text[2] = { ":(",":)" };


enum EN_OPERATION_TYPE{ OP_ADD=1, OP_SUB, OP_MUL, OP_DIV,OP_NOT_KNOWN };
char operation_type_char[5] = { ' ','+','-','*','/'};


enum EN_NUMBER_RANGE{EASY_MIN=1,EASY_MAX=99,MID_MIN=100,MID_MAX=999,HARD_MIN=1000,HARD_MAX=9999};

enum EN_QUIZ_RESULT{FAIL,PASS,QUIZ_RESULT_NOT_KNOWN};
string quiz_results_text[2] = { "Fail","Pass" };
string quiz_result_message_text[2] = { ":(",":)" };

enum class EN_BACKGROUND_COLOR {
	RED,
	GREEN,
	YELLOW,
	DEFAULT
};

enum EN_TAKE_ONOTHER_QUIZ {
	NO,YES
};

string take_another_quiz_text[2] = {"Y/y","N/n"};

struct Question {
    int question_number;
    int number_one;
    int number_two;
	EN_OPERATION_TYPE operation_type;
    double user_answer;
    double correct_answer;
	EN_QUESTION_RESULT question_result;
	

};

struct Quiz {
    int num_quetions;
	EN_QUESTIONS_LEVEL questions_level;
	EN_QUESTIONS_TYPE questions_type;
	Question questions[100];
	int number_right_answers;
	int number_wrong_answers;
	EN_QUIZ_RESULT quiz_result;

};


double read_positive_number(string message = "") {
	double input = 0;
	while (true) {
		cout << message << " ";
		if (cin >> input) {
			if (input <= 0) {
				cout << "Please enter a positive integer" << endl;
			}
			else {
				break;
			}
		}
		else {
			cout << "Please enter a valid integer" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
	return input;
}

bool is_number_in_range(int number, int from, int to) {

	return (number >= from && number <= to);
}

int generate_random_number(int from, int to) {
	return from + std::rand() % (to - from + 1);
}



void change_screen_color(EN_BACKGROUND_COLOR color) {
	switch (color) {
	case EN_BACKGROUND_COLOR::RED:
		system("color 4F");
		break;
	case EN_BACKGROUND_COLOR::GREEN:
		system("color 2F");
		break;
	
	case EN_BACKGROUND_COLOR::DEFAULT:
		system("color 07");
		break;
	default:
		break;
	}
}

bool is_in_range(int number, int from, int to) {
	return (number >= from && number <= to);
}

bool is_valid_questions_level(EN_QUESTIONS_LEVEL question_level) {
	return is_in_range(question_level, EN_QUESTIONS_LEVEL::EASY, EN_QUESTIONS_LEVEL::LVL_MIX);
}

EN_QUESTIONS_LEVEL generate_random_questions_level() {
	return ((EN_QUESTIONS_LEVEL)generate_random_number(EN_QUESTIONS_LEVEL::EASY, EN_QUESTIONS_LEVEL::HARD));
}

int generate_number_based_on_questions_level(EN_QUESTIONS_LEVEL question_level) {
	switch (question_level)
	{
	case EASY:
		return generate_random_number(EN_NUMBER_RANGE::EASY_MIN, EN_NUMBER_RANGE::EASY_MAX);
		break;
	case MID:
		return generate_random_number(EN_NUMBER_RANGE::MID_MIN, EN_NUMBER_RANGE::MID_MAX);
		break;
	case HARD:
		return generate_random_number(EN_NUMBER_RANGE::HARD_MIN, EN_NUMBER_RANGE::HARD_MAX);
		break;
	case LVL_MIX:
		return generate_number_based_on_questions_level(generate_random_questions_level());
		break;
	default:
		break;
	}
}
EN_QUESTIONS_LEVEL get_questions_level_based_on_number_generated(int number) {
	if (number >= EN_NUMBER_RANGE::EASY_MIN && number <= EN_NUMBER_RANGE::EASY_MAX) {
		return EN_QUESTIONS_LEVEL::EASY;
	}
	else if (number >= EN_NUMBER_RANGE::MID_MIN && number <= EN_NUMBER_RANGE::MID_MAX) {
		return EN_QUESTIONS_LEVEL::MID;
	}
	else {
		return EN_QUESTIONS_LEVEL::HARD;
	}
}

EN_OPERATION_TYPE generate_random_operation_type() {

	return (EN_OPERATION_TYPE)generate_random_number(EN_OPERATION_TYPE::OP_ADD, EN_OPERATION_TYPE::OP_DIV);
}

EN_OPERATION_TYPE get_operation_type(EN_QUESTIONS_TYPE questions_type) {

	switch (questions_type)
	{
	case ADD:
		return EN_OPERATION_TYPE::OP_ADD;
		break;
	case SUB:
		return EN_OPERATION_TYPE::OP_SUB;
		break;
	case MUL:
		return EN_OPERATION_TYPE::OP_MUL;
		break;
	case DIV:
		return EN_OPERATION_TYPE::OP_DIV;
		break;
	case QT_MIX:
		return generate_random_operation_type();
		break;
	default:
		break;
	}

}

EN_QUESTIONS_LEVEL read_questions_level() {
	EN_QUESTIONS_LEVEL questions_level;
	while (true) {
		questions_level = (EN_QUESTIONS_LEVEL)read_positive_number("Enter Question Level [1] " + questions_level_text[EN_QUESTIONS_LEVEL::EASY] + " [2] " +
			questions_level_text[EN_QUESTIONS_LEVEL::MID] + " [3] " + questions_level_text[EN_QUESTIONS_LEVEL::HARD] + " [4] " + questions_level_text[EN_QUESTIONS_LEVEL::LVL_MIX]);
		if (is_valid_questions_level(questions_level)) {
			break;
		}
	}
	return questions_level;
}

bool is_valid_questions_type(EN_QUESTIONS_TYPE question_type) {
	return is_in_range(question_type, EN_QUESTIONS_TYPE::ADD, EN_QUESTIONS_TYPE::QT_MIX);
}

EN_QUESTIONS_TYPE read_questions_type() {
	EN_QUESTIONS_TYPE question_type;
	while (true) {
		question_type = (EN_QUESTIONS_TYPE)read_positive_number("Enter Operation Type [1] " + question_type_text[EN_QUESTIONS_TYPE::ADD]
		+" [2] " + question_type_text[EN_QUESTIONS_TYPE::SUB] 
		+" [3] " + question_type_text[EN_QUESTIONS_TYPE::MUL]
		+" [4] "+ question_type_text[EN_QUESTIONS_TYPE::DIV]
		+" [5] " + question_type_text[EN_QUESTIONS_TYPE::QT_MIX]);
		if (is_valid_questions_type(question_type)) {
			break;
		}
	}
	return question_type;
}

double read_user_answer() {
	double user_answer = 0;
	while (true) {
		if (cin >> user_answer) {
			break;
		}
		else {
			cout << "Please enter a valid numerical answer ";
			cin.clear();
			cin.ignore(10000, '\n');
		}
	}
	return user_answer;
}

EN_QUESTION_RESULT get_question_result(const Question& question) {
	if (question.user_answer == question.correct_answer) {
		return EN_QUESTION_RESULT::CORRECT;
	}
	return EN_QUESTION_RESULT::WRONG;
}


void ask_question(Question& question,const int &question_number,const int &total_num_questions) {
	cout << "Question [" << question_number << "/" << total_num_questions << "]" << endl;
	cout << endl;
	cout << question.number_one << endl;
	cout << question.number_two << " " << operation_type_char[question.operation_type] << endl;
	cout << "_________" << endl;
	question.user_answer = read_user_answer();
	question.question_result = get_question_result(question);
}



double get_correct_result(const Question& question) {
	switch (question.operation_type)
	{
	case EN_QUESTIONS_TYPE::ADD :
		return question.number_one + question.number_two;
		break;
	case EN_QUESTIONS_TYPE::SUB:
		return question.number_one - question.number_two;
		break;
	case EN_QUESTIONS_TYPE::MUL:
		return question.number_one * question.number_two;
		break;
	case EN_QUESTIONS_TYPE::DIV:
		return question.number_one / question.number_two;
		break;

	default:
		break;
	}
}


void generate_question(Question& question, const Quiz& quiz) {
	question.number_one = generate_number_based_on_questions_level(quiz.questions_level);
	question.number_two = generate_number_based_on_questions_level(get_questions_level_based_on_number_generated(question.number_one));
	question.operation_type = get_operation_type(quiz.questions_type);
	question.correct_answer = get_correct_result(question);
}

void display_question_result(const Question &question) {
	if (question.question_result == EN_QUESTION_RESULT::WRONG) {
		cout << question_result_text[EN_QUESTION_RESULT::WRONG] << " answer " << question_result_message_text[EN_QUESTION_RESULT::WRONG] << endl;
		cout << "The right answer : " << question.correct_answer << endl;
		change_screen_color(EN_BACKGROUND_COLOR::RED);
	}
	else {
		cout << question_result_text[EN_QUESTION_RESULT::CORRECT] << " answer " << question_result_message_text[EN_QUESTION_RESULT::CORRECT] << endl;
		change_screen_color(EN_BACKGROUND_COLOR::GREEN);
	}
	cout << endl << endl;
}

void read_quiz_info(Quiz& quiz) {
	quiz.num_quetions = read_positive_number("How many question do you want to answer ? ");
	quiz.questions_level = read_questions_level();
	quiz.questions_type = read_questions_type();
}

int get_number_of_right_answers_per_quiz(const Quiz& quiz) {
	int number_of_correct_answers = 0;
	for (int i = 0; i < quiz.num_quetions; i++) {
		if (quiz.questions[i].question_result == EN_QUESTION_RESULT::CORRECT) {
			number_of_correct_answers++;
		}
	}
	return number_of_correct_answers;
}
int get_number_of_wrong_answers_per_quiz(const Quiz& quiz) {

	return (quiz.num_quetions - get_number_of_right_answers_per_quiz(quiz));
}

EN_QUIZ_RESULT get_quiz_result(const Quiz& quiz) {
	if (get_number_of_wrong_answers_per_quiz(quiz) != 0) {
		return EN_QUIZ_RESULT::FAIL;
	}
	return EN_QUIZ_RESULT::PASS;
}

void generate_quiz_results(Quiz& quiz) {
	
	quiz.number_right_answers = get_number_of_right_answers_per_quiz(quiz);
	quiz.number_wrong_answers = get_number_of_wrong_answers_per_quiz(quiz);
	quiz.quiz_result = get_quiz_result(quiz);
}

void display_quiz_result_header(const Quiz& quiz) {
	cout << "=================================" << endl;
	cout << " Final Results is " << quiz_results_text[quiz.quiz_result] << quiz_result_message_text[quiz.quiz_result] <<endl;
	cout << "=================================" << endl;
}

void change_screen_color_based_on_quiz_reult(const Quiz& quiz) {
	if (quiz.quiz_result == EN_QUIZ_RESULT::PASS) {
		change_screen_color(EN_BACKGROUND_COLOR::GREEN);
	}
	else {
		change_screen_color(EN_BACKGROUND_COLOR::RED);
	}
}

void display_quiz_results(Quiz& quiz) {
	display_quiz_result_header(quiz);
	cout << "Number of questions     : " << quiz.num_quetions << endl;
	cout << "Questions Level         : " << questions_level_text[quiz.questions_level] << endl;
	cout << "Operation Type          : " << question_type_text[quiz.questions_type] << endl;
	cout << "Number of right answers : " << quiz.number_right_answers << endl;
	cout << "Number of wrong answers : " << quiz.number_wrong_answers << endl;
	change_screen_color_based_on_quiz_reult(quiz);
	cout << "=================================" << endl;
}

void reset_screen_color() {
	change_screen_color(EN_BACKGROUND_COLOR::DEFAULT);
}
void clear_screen() {
	system("cls");
	reset_screen_color();
}

void reset_question(Question& question) {
	question.question_number=-1;
	question.number_one=-1;
	question.number_two=-1;
	question.operation_type=EN_OPERATION_TYPE::OP_NOT_KNOWN;
	question.user_answer=-1;
	question.correct_answer=-1;
	question.question_result= EN_QUESTION_RESULT::QUESTION_RESULT_NOT_KNOWN;
}

void reset_all_quiz_questions(Quiz& quiz) {
	for (int i = 0; i < quiz.num_quetions; i++) {
		reset_question(quiz.questions[i]);
	}
}

void reset_quiz(Quiz &quiz) {
	clear_screen();
	quiz.num_quetions=-1;
	quiz.questions_level=EN_QUESTIONS_LEVEL::LVL_NOT_KNOWN;
	quiz.questions_type= EN_QUESTIONS_TYPE::NOT_KNOWN;
	reset_all_quiz_questions(quiz);
	quiz.number_right_answers=-1;
	quiz.number_wrong_answers=-1;
	quiz.quiz_result = EN_QUIZ_RESULT::QUIZ_RESULT_NOT_KNOWN;
}

EN_TAKE_ONOTHER_QUIZ want_to_take_another_quiz() {
	char take_another_quiz = 'N';
	while (true) {
		cout << "Do you want to take another quiz " << take_another_quiz_text[EN_TAKE_ONOTHER_QUIZ::NO] << " " << take_another_quiz_text[EN_TAKE_ONOTHER_QUIZ::YES] << " ";
		if (cin >> take_another_quiz) {
			if (towupper(take_another_quiz) == 'Y' || towupper(take_another_quiz) == 'N') {
				break;
			}
		}
		else {
			cin.clear();
			cin.ignore(10000, '/n');
		}
	}
	return (toupper(take_another_quiz) == 'Y' ? EN_TAKE_ONOTHER_QUIZ::YES : EN_TAKE_ONOTHER_QUIZ::NO);
}

void start_quiz(Quiz& quiz) {
	
	while (true) {
		reset_quiz(quiz);
		read_quiz_info(quiz);
		for (int i = 0; i < quiz.num_quetions; i++) {
			generate_question(quiz.questions[i], quiz);
			ask_question(quiz.questions[i], i + 1, quiz.num_quetions);
			display_question_result(quiz.questions[i]);
		}
		generate_quiz_results(quiz);
		display_quiz_results(quiz);
		if (want_to_take_another_quiz() == EN_TAKE_ONOTHER_QUIZ::NO) {
			break;
		}
	}
	system("pause");
	
	
}

int main()
{
	srand(time(nullptr));
	Quiz quiz;
	start_quiz(quiz);
	return 0;
}

