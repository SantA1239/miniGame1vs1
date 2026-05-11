#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "additional.h"
using namespace std;

const double ARMOR_DEFEND_CONST = 50.;

const vector<string> DODGE_PHRASE = {
	""
};

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

			if (HP > 0) {
				cout << "Персонаж " << name << " получил " << dmg << " урона." << endl << "Осталось " << HP << " здоровья." << endl;
			}
			else {
				HP = 0;
				cout << "Персонаж " << name << " умер." << endl;
				dead = true;
			}
		}
		else {
			cout << DODGE_PHRASE[random::get_random_by_lover_upper_limit(0, DODGE_PHRASE.size() - 1)];
		}
	}

	// атака другого существа
	// для игрока
	void attack(Creature& unit, int& choise) {
		switch (choise)
		{
		// тяжелая атака
		case 1:
			unit.getDamage(damage + weapon.getDamageAttack(), 60);

		// быстрая атака
		case 2:
			unit.getDamage(damage + weapon.getDamageAttack(), 100);

		// лечение себя
		case 3:
			// лечение на 30%
			heal(HP_max * 0.3);

		default:
			break;
		}
		
	}

	// для моба
	void attack(Creature& unit) {
		unit.getDamage(damage + weapon.getDamageAttack());
	}

	// замена оружия
	void equipWeapon(string name_new_weapons, double new_val_att_weapons) {
		weapon.setValue(name_new_weapons, new_val_att_weapons);
	}

	// замена брони
	void equipArmor(string name_new_armor, double new_val_def_weapons) {
		weapon.setValue(name_new_armor, new_val_def_weapons);
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

	void loadParametrs(// имя героя
			string name,

		// основные характеристики
		double HP_max,
		double HP,
		double damage,
		bool dead,

		// оружие и броня
		Weapon weapon,
		Armor armor,

		// количество монет
		double money) {

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
		cout << "Вы восстановили здоровье. Текущее HP: " << HP << "/" << HP_max << endl;
	}
};

// класс магазина
class Shop {
public:
	void visit(Creature& player) {
		int choice;
		bool exiting = false;

		while (choice) {
			cout << "\n--- ДОБРО ПОЖАЛОВАТЬ В МАГАЗИН ---" << endl;
			cout << "Ваше золото: " << player.getMoney() << endl;
			cout << "1. Купить Стальной Меч (Урон +20) - 50 монет" << endl;
			cout << "2. Купить Усиленную Броню (Защита 5.0) - 60 монет" << endl;
			cout << "3. Купить Лечебное зелье (Восстанавливает 30 HP) - 20 монет" << endl;
			cout << "0. Выйти из магазина" << endl;
			cout << "Выберите действие: ";
			cin >> choice;

			switch (choice) {
			case 1:
				if (player.spendMoney(50)) {
					player.equipWeapon("Стальной Меч", 20);
					cout << "Вы купили Стальной Меч!" << endl;
				}
				else cout << "Недостаточно золота!" << endl;
				break;

			case 2:
				if (player.spendMoney(60)) {
					player.equipArmor("Усиленная Броня", 5.0);
					cout << "Вы купили Усиленную Броню!" << endl;
				}
				else cout << "Недостаточно золота!" << endl;
				break;

			case 3:
				if (player.spendMoney(20)) {
					player.heal(30);
				}
				else cout << "Недостаточно золота!" << endl;
				break;

			case 0:
				break;

			default:
				cout << "Неверный выбор." << endl;
			}
		}
	}
};

// функция игры
bool round(Creature& player, Creature& monster) {
	bool who_fight = true;
	while (player.isLife() && monster.isLife())
	{
		if (who_fight) {
			int choise;
			choise = valid::valid_num("Введите действие: сильная атака (1), быстрая атака (2), лечиться (3)...: ", "Ошибка ввода! Повторите: ", 1, 3);
				
			player.attack(monster, choise);
		}
			
		else
			monster.attack(player);

		who_fight = !who_fight;
	}

	return player.isLife();
}

ofstream operator << (ofstream& fin, Creature& player) {
	for (double parametr : player.saveParameters())
		fin << parametr << ' ';

	// переменные для сохранения
	string t_name;
	double t_val;

	// сохранение оружия
	player.saveInfoWeapon(t_name, t_val);
	fin << t_name << ' ' << t_name;

	// сохранение оружия
	player.saveInfoArmor(t_name, t_val);
	fin << t_name << ' ' << t_name;
}

ifstream operator >> (ifstream& fin, Creature& player) {
	
	
	;
}

void saveGame(Creature& player, int& round) {
	ofstream fin_save("save_game.txt");

	fin_save << player;

	fin_save << round << ' ';

	fin_save.close();
}

void loadGame(Creature& player, int& round) {
	ifstream fin_load;

	fin_load >> player;

	fin_load.close();
}

int main() {
	setlocale(LC_ALL, "ru");
	
	// объект класса игрока
	Creature player("Player", 100, 5, 0, "Меч", 10, "Латы", 3);
	// количество раундов
	int round = 1;
	int final_round = 100;

	bool who_fight = true;
	
	while (round < final_round) {
		// действие: бой, сохраниение и т. д.
		char action;
		cout << "Сохраниться (S), в бой (B)";
		cin >> action;
		
		while (!(action == 'S' || action == 'B'))
		{
			cout << "Ошибка! Повторите попытку: ";
			cin >> action;
		}


	}

	return 0;
}