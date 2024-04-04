#include "player.h"

const std::string Player::DEFAULT_NAME = "匿名";

bool Player::operator<(const Player& other) const
{
	return player_status() < other.player_status();
}

bool Player::operator>(const Player& other) const
{
	return player_status() > other.player_status();
}

unsigned int Player::money() const
{
	return _money;
}

Player::PlayerStatus Player::player_status() const
{
	return _status;
}

int Player::hand_points() const
{
	return _hand_points;
}

std::string Player::name() const
{
	return _name;
}

int Player::hand_size() const
{
	return static_cast<int>(_hand_cards.size());
}

Player& Player::set_money(const unsigned int money)
{
	if (money > MAX_MONEY) {
		throw std::invalid_argument("The 'money' must not exceed "
			+ std::to_string(MAX_MONEY) +
			" RMB.");
	}

	_money = money;

	return (*this);
}

Player& Player::set_status(const PlayerStatus ps)
{
	_status = ps;

	return (*this);
}

Player& Player::set_name(const std::string name)
{
	_name = CheckName(name);

	return (*this);
}

Player& Player::AddCard(const Card& card)
{
	_hand_cards.push_back(card);
	this->CalculateHandPoints();	// 重新计算点数

	return (*this);
}

Player& Player::ClearCard()
{
	_hand_cards.clear();
	this->CalculateHandPoints();

	return (*this);
}

unsigned int Player::Raise(const unsigned int money)
{
	if (_money < money) {
		throw std::invalid_argument("Insufficient account balance. The account balance is "
			+ std::to_string(_money)
			+ " RMB, which is not enough to make a payment of "
			+ std::to_string(money)
			+ " RMB.");
	}

	_money -= money;

	return money;
}

unsigned int Player::LowerBet(const unsigned int money)
{
	unsigned int money_buf = _money + money;
	this->set_money(money_buf);

	return money;
}

std::string Player::DisplayHandCards(bool masked) const
{
	std::stringstream ss;

	for (int row = 0; row < 6; row++) {
		for (int i = 0; i < _hand_cards.size(); i++) {
			ss << _hand_cards[i].Display(row, masked) << " ";
		}
		ss << "\n";
	}

	return ss.str();
}

std::string Player::DisplayHandPoints(bool masked) const
{
	std::stringstream ss;

	if (masked) {
		ss << darkGray << "??" << def;
	}
	else {
		if (_hand_points > 21) {
			ss << red;		// 溢出用红色
		}
		else {
			ss << green;	// 未溢出用绿色
		}

		ss << std::to_string(_hand_points) << def;
	}

	return ss.str();
}

std::string Player::DisplayHandCP(bool masked, bool is_player_self) const
{
	std::string points_hint = _name + " 的点数: ";									// 点数提示文字
	std::string nameWidthSeparator(_name.length(), '-');							// 玩家姓名文字等宽分隔符
	std::string hintWidthSeparator(points_hint.length(), '-');						// 点数提示文字等宽分隔符
	std::stringstream ss;

	ConsoleColor::Modifier border_color = (is_player_self ? blue : lightMagenta);	// 边框颜色

	ss << border_color << "######====-" << nameWidthSeparator << "-====######===~---··\n" << def
		<< border_color << "|========> " << def << _name << border_color << " <========|  " << def << points_hint << this->DisplayHandPoints(masked) << "\n"
		<< border_color << "###=====---" << nameWidthSeparator << "---=====###=====~"<< hintWidthSeparator <<"···\n\n" << def
		<< this->DisplayHandCards(masked) << "\n";

	return ss.str();
}

Player& Player::Save(std::ofstream& outFile)
{
	// 保存_name
	// 首先，保存字符串的长度
	size_t nameLength = _name.length();
	outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
	// 然后，保存字符串本身
	outFile.write(_name.c_str(), nameLength);

	// 保存_status
	// 因为PlayerStatus是枚举类型，可以直接将其底层类型（通常是int）写入
	auto statusInt = static_cast<int>(_status);  // 先将枚举转换为整数
	outFile.write(reinterpret_cast<const char*>(&statusInt), sizeof(statusInt));

	// 保存_money
	outFile.write(reinterpret_cast<const char*>(&_money), sizeof(_money));

	return (*this);
}

bool Player::Load(std::ifstream& inFile)
{
	// 将文件指针设置到文件的开头
	inFile.seekg(0);

	// 读取_name
	// 首先，读取字符串的长度
	size_t nameLength;
	if (!inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) {
		return false; // 读取失败
	}
	// 根据长度读取字符串本身
	_name.resize(nameLength);
	if (!inFile.read(&_name[0], nameLength)) {
		return false; // 读取失败
	}

	// 读取_status
	int statusInt;
	if (!inFile.read(reinterpret_cast<char*>(&statusInt), sizeof(statusInt))) {
		return false; // 读取失败
	}
	_status = static_cast<PlayerStatus>(statusInt);  // 将整数转换回枚举

	// 读取_money
	if (!inFile.read(reinterpret_cast<char*>(&_money), sizeof(_money))) {
		return false; // 读取失败
	}

	_hand_points = 0;

	return true;
}

std::string Player::CheckName(const std::string name) const
{
	std::size_t name_length = name.length();
	if (name_length < MIN_NAME_LENGTH || name_length > MAX_NAME_LENGTH) {	// 检查名字长度
		std::stringstream err_ss;
		err_ss << "The name must be between "
			<< std::to_string(MIN_NAME_LENGTH)
			<< " and "
			<< std::to_string(MAX_NAME_LENGTH)
			<< " characters long.";
		throw std::invalid_argument(err_ss.str());
	}

	return name;
}

unsigned int Player::CheckMoney(const unsigned int money) const
{
	if (money < 0U || money > MAX_MONEY) {
		throw std::invalid_argument("Invalid account amount setting. The balance must not be less than 0 RMB and cannot exceed "
			+ std::to_string(MAX_MONEY)
			+ " RMB.");
	}

	return money;
}

Player& Player::CalculateHandPoints()
{
	_hand_points = 0;	// 必须先初始化为 0，重新计算手中点数

	for (std::vector<Card>::iterator it = _hand_cards.begin(); it != _hand_cards.end(); it++) {
		int cardPoint = (*it).points();
		_hand_points += cardPoint;
	}

	return (*this);
}


