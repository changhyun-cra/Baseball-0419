#include <stdexcept>
#include <string>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question)
		: question(question) {

	}

	bool isDuplicatedNumber(const string guessNumber) {
		if (guessNumber[0] == guessNumber[1] ||
			guessNumber[1] == guessNumber[2] ||
			guessNumber[0] == guessNumber[2]) {
			return true;
		}
		return false;
	}

	void assertIllegalArgument(const string& guessNumber)
	{
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number");
		}
	}

	int checkStrike(const string& guessNumber) {
		int strike = 0;
		for (int idx = 0; idx < question.size(); idx++) {
			if (guessNumber[idx] == question[idx]) {
				strike++;
			}
		}
		return strike;
	}

	int checkBall(const string& guessNumber) {
		int ball = 0;
		for (char ch : guessNumber) {
			int place = question.find(ch);
			if (place < 0) continue;
			ball++;
		}
		return ball;
	}

	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);
		if (guessNumber == question) {
			return { true, 3,0 };
		}

		return { false, checkStrike(guessNumber), checkBall(guessNumber)-checkStrike(guessNumber)};
	}
	
private:
	string question;
};