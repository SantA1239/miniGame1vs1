#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "additional.h"
#include <chrono>
#include <thread>
using namespace std;

const string INFORMATION_ABOUT_DEVELOPMENT = "\t\t\tРазработчики:\nТим-лид: Сафронов Егор\nДизайнер: Торасян Размик\nСценарист: Садыков Арсен\nПрограммисты: Гаврилов Матвей, Уколов Глеб, Щербаков Петр";

const double ARMOR_DEFEND_CONST = 50.;

const vector<string> PLOT_PHRASE = {
	""
};

const vector<string> DODGE_PHRASE = {
/*	"Уга буга политех",*/ 
	"Атака достигла лишь тени противника", 
	"Удар прошёл сквозь дымку — враг уже сместился в сторону", 
	"Меч описал красивую дугу. Красивую, но бесполезную", 
	"Это было близко… слишком близко"
};
const vector<std::string> opponents = {
		"гном детского сада",
		"Саид маринованый",
		"Петр колдун света",
		"гоблин",
		"трушный математик Егор",
		"Глеб Каловрат",
		"Размик советник Короля",
		"Матвей Общоровский",
		"Арсен одинокий дворецкий",
		"болтный симбиот",
		"медведь",
		"спайк",
		"ворон",
		"слизь",
		"монстр-дерево",
		"наблюдатель",
		"крыса",
		"сабака",
		"матодор"
};

vector<std::string> DAMAGE_PHRASES = {
	"А ну иди сюда",
	"Сам напросился",
	"За дедов!!!",
	"Хаа Хий",
	"Получай, гад!",
	"Земля помнит!",
	"На, откуси!",
	"Хрясь!",
	"За родину!",
	"Жизнь - боль, я - её причина",
	"Где мои 5000 тыщ?",
	"Моя бабушка лучше тебя дерётся",
	"Полный вперёд!",
	"Ща как дам!",
	"Держи угощение!",
	"Это тебе за всех!",
	"Раз, два — понял!",
	"Я как встану, а ты вылетишь!",
	"Куда полез, шерше ля фам!",
	"С разворота!",
	"Ниже пояса не бью... Сегодня",
	"Ну ты нарвался",
	"Прилетело?"
};

//vector<std::string> receive_damage_phrases = {
//	"Ухтыж",
//	"Потеря ноги — не проблема",
//	"Щас попоёшь ты у меня",
//	"Опа, а ты бить не умеешь",
//	"Е, давай помягче",
//	"В баню я бы с тобой не пошёл",
//	"Так-так, проржавело немного",
//	"Лёгкий щиточек, не боись",
//	"Это всё? А я боялся",
//	"Не по адресу прилетело",
//	"Упс, просили же не сюда",
//	"Почему так больно?",
//	"Котэ, беги, убивают",
//	"За базар ответишь",
//	"Ты поступил не по пацански",
//	"Чувак, не жёстко, но обидно",
//	"Подумаешь, ты ещё не видел мой второй нос",
//	"Слабовато, жми давай!",
//	"Зубы целы — уже победа",
//	"Пока живой, значит не страшно",
//	"Шрамы украшают...",
//	"Не понял. Повтори на брудершафт",
//	"Вали всё, что есть — заживёт",
//	"Быстрее мешешь, у меня обед"  // предположил, что "межешь" = "мелешь" (говоришь)
//};

vector<std::string> KILL_PHRASES = {
	"Улетела шваль",
	"Туда его",
	"Кто победитель, а?",
	"Чё по вещам",
	"Халява",
	"Шикарно просто, шикарно",
	"Иди поплач",
	"Следующий!",
	"Алло, это рай? Примите одного",
	"Всё, накрылся тазик",
	"Будет тебе наука",
	"Вот и вся любовь",
	"Похороны за твой счёт",
	"Место свободно, кто следующий?",
	"Спи спокойно, дорогой товарищ",
	"Победитель получает всё, а ты — землю",
	"Ещё один — в музей восковых фигур",
	"Вырублен. Иди розетку искать",
	"На покой, старина",
	"Пусть земля будет пухом... Или песком",
	"Анекдот рассказать над гробом?",
	"Упокойся с миром, а я с чистой совестью",
	"Оформили путёвку в лучший мир"
};

//vector<std::string> purchase_phrases = {
//	"Продай мне... ну это самое...",
//	"А что у тебя есть интересного?",
//	"Дай чего-нибудь, сам не знаю чего",
//	"Мне бы того... ну ты понял",
//	"Продай удачу за 100 рублей",
//	"А можно мне счастья? Побольше, килограмма два",
//	"Мне по приколу чего-нибудь",
//	"Сделайте мне круто, я заплачу",
//	"Продай мне мотивацию, она кончилась",
//	"Есть у тебя то, от чего башка не болит?",
//	"Дай мне то, чё я ещё не пробовал",
//	"А есть верное решение всех проблем?",
//	"Мне бы уверенности на литр",
//	"А есть что-то дешёвое, но чтоб вау?",
//	"Дай мне что-нибудь, что мама одобрит",
//	"Царь во дворце — царь",
//	"Ну и жмотяра",
//	"Скажи это моему мечу",
//	"Может, так рассчитаемся... Забыл, ты же по монстрам",
//	"Я тебя тут защищаю, а ты мне пенное не можешь подарить",
//	"Мы все под одним небом живём. Ты мне — я помогу тебе. Дай скидку"
//};

namespace {

	const vector<string>& monsterArt() {
		static const vector<string> lines = {
			R"(		          		        _   ,			  ,      ,      )",
			R"(		          	  	     _,/ \	             /(.-""-.)\     )",
			R"(		      	  	        (_/  /	         |\  \/      \/  /| )",
			R"(	  |	   \      	  	     /  /	         | \ / ====== \ / | )",
			R"(	  |	    \               /  /	         \  '-\  ()  /-'  / )",
			R"(	  |    _/     	  	   /  /	              '.   \ -- /   .'  )",
			R"(    |    /              /  /                  '--|    |--'    )",
			R"(	  |   |   	  	  /__/  /__/                   |    |       )",
			R"(	  |   |_____________/  \			    	   |    |       )",
			R"(	  |_________________\__/  			    	   |    |       )",
			R"(	    								           /    \       )",
			R"(	    								                        )"
		};
		return lines;
	}

	const vector<string>& monsterArtMirrored() {
		static const vector<string> lines = {
			R"(      ,      ,  			                                 	                        )",
			R"(    /\).-""-.(/\                          / \,_                 	                    )",
			R"( |/ \/\      /\/  \|                      \  \_)                 	                    )",
			R"( |   \ ====== /    |                       \  \             /    |                  	)",
			R"( \  '-\  )(  /-'  /                         \  \            /     |                  	)",
			R"(   '.  \ -- /   .'                           \  \           \_    |                 	)",
			R"(    '--|    |--'                              \  \           \    |                   )",
			R"(       |    |                               \__\  \__\        |   |                 	)",
			R"(       |    |   	    	                     /  \___________|   |                 	)",
			R"(       |    |   	    	                     \__/_______________|                 	)",
			R"(       \    /           								    	                        )",
			R"(                        								    	                        )"
		};
		return lines;
	}

	void pauseBattleGraphic() {
		cout.flush();
		this_thread::sleep_for(chrono::seconds(2));
	}

} // namespace

void drawMonster() {
	for (const string& line : monsterArt())
		cout << line << endl;
}

void drawMonsterMirrored() {
	for (const string& line : monsterArtMirrored())
		cout << line << endl;
}

// Зеркальная псевдографика перед атакой монстра (1 — тяжёлая, 2 — быстрая)
void showMonsterTurnMirrored(int m_action) {
	if (m_action != 1 && m_action != 2)
		return;
	cout << "\n";
	if (m_action == 1)
		cout << "       >>> МОНСТР: ТЯЖЁЛЫЙ УДАР <<<\n\n";
	else
		cout << "       >>> МОНСТР: БЫСТРЫЙ УДАР <<<\n\n";
	drawMonsterMirrored();
	pauseBattleGraphic();
	cout << "\n";
}

// класс брони
class Armor {
private:
	string name_armor;
	double val_armor;

public:
	// функция возврата получения урона с учетом брони
	double getDamageArmor(int damage) {
		return damage * (1 - val_armor / (val_armor + ARMOR_DEFEND_CONST));
	}

	string getName() {
		return name_armor;
	}

	// установить значение назнания брони и ее защиты при ее смене
	void setValue(string new_name_armor, double new_value_armor) {
		name_armor = new_name_armor;
		val_armor = new_value_armor;
	}

	double getValArmor() {
		return val_armor;
	}
};

// класс оружия
class Weapon {
private:
	string name_weapon;
	double val_attack;

public:
	// функция возврата атаки с учетом оружия
	double getDamageAttack() {
		return val_attack;
	}

	string getName() {
		return name_weapon;
	}

	// установить значение назнания оружия и его атаки при его смене
	void setValue(string new_name_weapon, double new_value_weapon) {
		name_weapon = new_name_weapon;
		val_attack = new_value_weapon;
	}
};

// класс сущности
class Creature {
private:
	// имя героя
	string name;

	// основные характеристики
	double HP_max;
	double HP;
	double damage;
	bool dead;

	// оружие и броня
	Weapon weapon;
	Armor armor;

	// количество монет
	double money;

public:
	Creature() {}
	Creature(string name_unit, double HP_unit, double damage_unit, double money_unit, 
		string start_weapon, double value_attack_weapon,
		string start_armor, double value_def_armor) {

		name = name_unit;
		HP = HP_unit;
		HP_max = HP_unit;
		damage = damage_unit;
		money = money_unit;

		if (HP > 0)
			dead = false;
		else
			dead = true;

		weapon.setValue(start_weapon, value_attack_weapon);
		armor.setValue(start_armor, value_def_armor);
	}

	Creature(string name_unit, double HP_unit, double damage_unit,
		string start_weapon, double value_attack_weapon,
		string start_armor, double value_def_armor) {

		name = name_unit;
		HP = HP_unit;
		HP_max = HP_unit;
		damage = damage_unit;

		if (HP > 0)
			dead = false;
		else
			dead = true;

		weapon.setValue(start_weapon, value_attack_weapon);
		armor.setValue(start_armor, value_def_armor);
	}

	// жив ли персонаж?
	bool isLife() {
		return !dead;
	}

	// получение урона
	void getDamage(int dmg, int chance) {
		if (random::if_chance(chance)) {
			HP -= armor.getDamageArmor(dmg);
			cout << "\n\n-------------------------------------------------------------------\n";
			if (HP > 0) {
				cout << "\n>  " << name << " получил урон!  <"
					<< "\n   |- Урон: " << dmg
					<< "\n   |- Здоровье: " << HP << "/" << HP_max << endl;
			}
			else {
				HP = 0;
				cout << "Персонаж " << name << " умер." << endl;
				dead = true;
			}
			cout << "\n-------------------------------------------------------------------\n\n";
		}
		else {
			cout << "\n-------------------------------------------------------------------\n";
			cout << DODGE_PHRASE[random::get_random_by_lover_upper_limit(0, DODGE_PHRASE.size() - 1)];
			cout << "\n-------------------------------------------------------------------\n";
		}
	}

	// атака другого существа
	void attack(Creature& unit, int choise) {
		switch (choise)
		{
		// тяжелая атака
		case 1:
			unit.getDamage((damage + weapon.getDamageAttack()) * 1.15, 60);
			break;

		// быстрая атака
		case 2:
			unit.getDamage(damage + weapon.getDamageAttack(), 100);
			break;

		// лечение себя
		case 3:
			// лечение на 15%
			heal(HP_max * 0.15);
		}
		
	}

	// замена оружия
	void equipWeapon(string name_new_weapons, double new_val_att_weapons) {
		weapon.setValue(name_new_weapons, new_val_att_weapons);
	}

	// замена брони
	void equipArmor(string name_new_armor, double new_val_def_weapons) {
		armor.setValue(name_new_armor, new_val_def_weapons);
	}

	// функции для сохранения персонажа
	// сохранение основных параметров
	vector<double> saveParameters() {
		vector<double> result;
		result.reserve(4);

		result.push_back(HP);
		result.push_back(HP_max);
		result.push_back(damage);
		result.push_back(money);
	}

	// сохранение оружия
	void saveInfoWeapon(string& name_weapon, double& val_attack) {
		name_weapon = weapon.getName();
		val_attack = weapon.getDamageAttack();
	}

	// сохранение брони
	void saveInfoArmor(string& name_armor, double& val_armor) {
		name_armor = armor.getName();
		val_armor = armor.getValArmor();
	}


	// Работа с деньгами
	double getMoney() const { return money; }

	void addMoney(double amount) { money += amount; }

	bool spendMoney(double amount) {
		if (money >= amount) {
			money -= amount;
			return true;
		}
		return false;
	}

	// Лечение
	void heal(double amount) {
		HP += amount;
		if (HP > HP_max) HP = HP_max;
		cout << name << " восстановили здоровье.Текущее HP : " << HP << " / " << HP_max << endl;
	}

	// дружественные функции
	// сохранение/загрузка
	friend ofstream& operator << (ofstream&, Creature&);
	friend ifstream& operator >> (ifstream&, Creature&);

	// вывод характеристик для отладки
	void print_parametrs() {
		cout << "Имя: " << name << '\n' <<
			"Жизни: " << HP << '\n' <<
			"Жизни макс.: " << HP_max << '\n' <<
			"Урон: " << damage << '\n' <<
			"Монеты: " << money << '\n' <<
			"Имя оружия: " << weapon.getName() << '\n' <<
			"Значение урона: " << weapon.getDamageAttack() << '\n' <<
			"Имя брони: " << armor.getName() << '\n' <<
			"Значение брони: " << armor.getValArmor() << '\n';
	}
};

// класс магазина
class Shop {
public:
	void visit(Creature& player) {
		int choice = 100;
		bool exiting = false;

		while (!exiting) {
			cout << "\n--- ДОБРО ПОЖАЛОВАТЬ В МАГАЗИН ---" << endl;
			cout << "Ваше золото: " << player.getMoney() << endl;
			cout << "1. Купить Стальной Меч (Урон +20) - 50 монет" << endl;
			cout << "2. Купить Усиленную Броню (Защита 5.0) - 60 монет" << endl;
			cout << "3. Купить Лечебное зелье (Восстанавливает 30 HP) - 20 монет" << endl;
			cout << "0. Выйти из магазина" << endl;
			cout << "Выберите действие: ";
			cin >> choice;
			cin.clear();
			cin.ignore(1000, '\n');

			switch (choice) {
			case 1:
				if (player.spendMoney(50)) {
					player.equipWeapon("Стальной_Меч", 20.);
					cout << "Вы купили Стальной Меч!" << endl;
				}
				else cout << "Недостаточно золота!" << endl;
				break;

			case 2:
				if (player.spendMoney(60)) {
					player.equipArmor("Усиленная_Броня", 5.);
					cout << "Вы купили Усиленную Броню!" << endl;
				}
				else cout << "Недостаточно золота!" << endl;
				break;

			case 3:
				if (player.spendMoney(20)) {
					player.heal(30.);
				}
				else cout << "Недостаточно золота!" << endl;
				break;

			case 0:
				exiting = !exiting;
				break;

			default:
				cout << "Неверный выбор." << endl;
			}
		}
	}
};

ofstream& operator << (ofstream& fout, Creature& player) {

	fout << player.name << ' ' << 
		player.HP << ' ' <<
		player.HP_max << ' ' <<
		player.damage << ' ' <<
		player.money << ' ';

	// переменные для сохранения
	string t_name;
	double t_val;

	// сохранение оружия
	player.saveInfoWeapon(t_name, t_val);
	fout << t_name << ' ' << t_val << ' ';

	// сохранение оружия
	player.saveInfoArmor(t_name, t_val);
	fout << t_name << ' ' << t_val << ' ';

	return fout;
}

ifstream& operator >> (ifstream& fin, Creature& player) {
	// имя героя
	fin >> player.name;

	// основные характеристики
	fin >> player.HP;
	fin >> player.HP_max;
	
	fin >> player.damage;
	fin >> player.money;

	string t_w_name;
	int t_w_val;

	fin >> t_w_name >> t_w_val;
	player.equipWeapon(t_w_name, t_w_val);

	string t_a_name;
	int t_a_val;
	fin >> t_a_name >> t_a_val;
	player.equipArmor(t_a_name, t_a_val);
	
	return fin;
}

void saveGame(Creature& player, int& round) {
	ofstream fin_save("save_game.txt");

	fin_save << player;

	fin_save << round << ' ';

	fin_save.close();
}

void loadGame(Creature& player, int& round) {
	ifstream fin_load("save_game.txt");

	// Проверка на пустой файл
	if (fin_load.peek() == ifstream::traits_type::eof()) {
		cout << "Файл сохранения пуст! Загрузка невозможна." << endl;
		fin_load.close();
		return;
	}

	// Пытаемся загрузить данные
	if (fin_load >> player >> round) {
		cout << "Игра успешно загружена!" << endl;
	}
	else {
		cout << "Ошибка при загрузке! Файл поврежден." << endl;
	}

	fin_load.close();
}

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));
	
	cout << INFORMATION_ABOUT_DEVELOPMENT << "\n-------------------------------------------------------------------------\n";

	Creature player("Player", 100, 5, 20, "Меч", 10, "Латы", 3);
	Shop shop;
	int round = 1;
	const int FINAL_ROUND = 25;

	char loading;
	cout << "Загрузиться? (y/n): ";
	cin >> loading;
	if (loading == 'y') {
			loadGame(player, round);
	}
	while (player.isLife() && round <= FINAL_ROUND) {
		cout << "================================" << endl;
		cout << "РАУНД " << round << " ИЗ " << FINAL_ROUND << endl;

		bool round_processed = false; // короче флаг чтобы в бой не заходитьь если выбрали сохранение

		// 1. Магазин (каждые 5 раундов)
		if (round % 5 == 0 && round != FINAL_ROUND) {
			cout << "[!]  На пути Кировский РЫНОК!" << endl;
			shop.visit(player);
		}

		// 2. Выбор действия
		char action;
		cout << "Сохраниться (S), В бой (B): ";
		cin >> action;

		if (action == 'S' || action == 's') {
			saveGame(player, round);
			cout << "Игра сохранена." << endl;

		}
		else if (action == 'B' || action == 'b') {
			// 3. Создание противника
			string m_name;
			if (round == FINAL_ROUND) {
				m_name = "БОСС Канабис";
			}
			else {

				int randomIndex = random::get_random_by_lover_upper_limit(0, opponents.size() - 1);
				m_name = opponents[randomIndex];
			}

			double m_hp = (round == FINAL_ROUND) ? 250.0 : (50.0 + round * 5);
			double m_dmg = (round == FINAL_ROUND) ? 20.0 : (5.0 + round);

			Creature monster(m_name, m_hp, m_dmg, "Когти", 5, "Шкура", 2);
			bool who_fight = true;

			cout << "--- НАЧАЛО БОЯ С " << m_name << " ---" << endl;


			while (player.isLife() && monster.isLife()) {
				if (who_fight) {					
					int choise = valid::valid_num("Ваш ход (1-тяжелая, 2-быстрая, 3-хил): ", "Ошибка: ", 1, 3);
					cout << endl  << " >> " << DAMAGE_PHRASES[random::get_random_by_lover_upper_limit(0, DAMAGE_PHRASES.size() - 1)] << endl;
					//if (choise < 3)
					//	drawMonster();
					player.attack(monster, choise);
				}
				else {
					int choise = random::get_random_by_lover_upper_limit(1, 3);
					cout << "[Ход монстра] " << ((choise == 1) ? "Тяжелая атака\n" : (choise == 2) ? "Быстрая атака\n" : "Хил\n");
					cout << " >> " << DAMAGE_PHRASES[random::get_random_by_lover_upper_limit(0, DAMAGE_PHRASES.size() - 1)] << endl;
					monster.attack(player, choise);
				}
				who_fight = !who_fight;
			}

			// 4. Итоги боя
			if (player.isLife()) {
				cout << "Вы победили в раунде " << round << "!" << endl;
				player.addMoney(30);

				if (round == FINAL_ROUND) {
					cout << "ПОБЕДА! Win!" << endl;
				}

				round++;
				round_processed = true;
			}
			else {
				cout << "Ты умер в раунде " << round << endl;
			}
		}
	}

	return 0;
}