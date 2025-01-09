#include<iostream>
#include<cmath>
#include <string>
using namespace std;

class Character
{
protected:
	static const int EXP_LV = 100;
	string name;
	int hp;
	int level;
	int exp;
	int power;
	int knowledge;
	int luck;
	int mp;
	void levelUp(int hInc, int pInc, int kInc, int lInc);
public:
	Character(string n, int lv, int h, int po, int kn, int lu, int mp);
	virtual void print();
	virtual void beatMonster(int exp) = 0;
	virtual void setHP(int) = 0;
	virtual int getHP() = 0;
	virtual int getAttack() = 0;
	string getName();
};

Character::Character(string n, int lv, int h, int po, int kn, int lu, int mp) : name(n), level(lv), exp(pow(lv - 1, 2) * EXP_LV), hp(h), power(po), knowledge(kn), luck(lu), mp(mp) { }

string Character::getName()
{
	return this->name;
}

void Character::levelUp(int hInc, int pInc, int kInc, int lInc) 
{
	this->level++;
	this->hp += hInc;
	this->power += pInc;
	this->knowledge += kInc;
	this->luck += lInc;
}

void Character::print()
{
	cout << this->name << ": " << this->level << " (" << this->exp << "/" << pow(this->level, 2) * EXP_LV << "), ";
	if(this->hp >= 0)
		cout << this->hp;
	else
		cout << "0";

	cout << "-" << this->power << "-" << this->knowledge << "-" << this->luck << "-" << this->mp << "\n";}

class Warrior : public Character
{
private:
	static const int HP_LV = 100;
	static const int PO_LV = 10;
	static const int KN_LV = 5;
	static const int LU_LV = 5;
public:
	Warrior(string n, int lv = 1) : Character(n, lv, lv* HP_LV, lv * PO_LV, lv * KN_LV, lv * LU_LV ,0) {}
	void print() { cout << "Warrior "; Character::print(); }
	int getHP() { return hp; } 
	void setHP(int hp) { this->hp = hp; } 
	int getAttack() { return power; }
	void beatMonster(int exp) // function overriding
	{
		this->exp += exp;
		while(this->exp >= pow(this->level, 2) * EXP_LV)
			this->levelUp(HP_LV, PO_LV, KN_LV, LU_LV);
	}
};

class Wizard : public Character
{
private:
	static const int HP_LV = 80;
	static const int PO_LV = 4;
	static const int KN_LV = 15;
	static const int LU_LV = 7;
	static const int MP_LV = 50;
public:
	Wizard(string n, int lv = 1) : Character(n, lv, lv * HP_LV, lv * PO_LV, lv * KN_LV, lv * LU_LV, lv * MP_LV) {}
	void print() { cout << "Wizard "; Character::print(); }
	int getHP() { return hp; } 
	void setHP(int hp) { this->hp = hp; } 
	int getAttack() { return knowledge; }
	void beatMonster(int exp) // function overriding
	{
		this->exp += exp;
		while(this->exp >= pow(this->level, 2) * EXP_LV)
			this->levelUp(HP_LV, PO_LV, KN_LV, LU_LV);
	}
};

class TimeTraveler : public Character 
{
private:
    static const int HP_LV = 80;
    static const int MP_LV = 50;
    static const int PO_LV = 5;
    static const int KN_LV = 15;
    static const int DF_LV = 8;
    static const int LU_LV = 5;
public:
    TimeTraveler(string n, int lv = 1) : Character(n, lv, lv * HP_LV, lv * PO_LV, lv * KN_LV, lv * LU_LV, lv * MP_LV) {}

    void print() override 
	{
        cout << "TimeTraveler ";
        Character::print();
    }

    int getHP() override { return hp; }
    void setHP(int hp) override { this->hp = hp; }
    int getAttack() override { return knowledge; }

    void beatMonster(int exp) override 
	{
        this->exp += exp;
        while (this->exp >= pow(this->level, 2) * EXP_LV)
            this->levelUp(HP_LV, PO_LV, KN_LV, LU_LV);
    }
    
	// �ɶ��^��
    void timeRewind(Character* team[], int count) 
	{
    	static bool hasNotified = false;
    	if (mp >= 50) 
		{
        	for (int i = 0; i < count; i++) 
			{
            	if (team[i]->getHP() > 0)
                	team[i]->setHP(team[i]->getHP() + 30);
       		}
        	mp -= 50;
        	hasNotified = false; // ���\�ϥΧޯ�
        	cout << name << " used Time Rewind! The team recovered HP.\n";
    	} 
		else if (!hasNotified) 
		{
        	cout << name << " does not have enough MP for Time Rewind!\n";
        	hasNotified = true; // �]�w�����w�g��ܹL
    	}
	}
	
    // �ɶ��[�t
    void timeAcceleration(Character* team[], int count) 
	{
    	static bool hasNotified = false;
    	if (mp >= 30) 
		{
        	cout << name << " used Time Acceleration! Team gains double EXP next round.\n";
        	for (int i = 0; i < count; i++) 
			{
            	if (team[i]->getHP() > 0) 
				{
                	team[i]->beatMonster(100); // �C�H��o�B�~�g���
            	}
        	}
        	mp -= 30;
        	hasNotified = false; // ���\�ϥΧޯ�
    	} 
		else if (!hasNotified) 
		{
        	cout << name << " does not have enough MP for Time Acceleration!\n";
        	hasNotified = true; // �]�w�����w�g��ܹL
    	}
	}
    // �ᵲ�ɶ�
    void timeStasis() 
	{
    	static bool hasNotified = false;
    	if (mp >= 70) 
		{
        	cout << name << " used Time Stasis! Monster skips its attack this round.\n";
        	mp -= 70;
        	hasNotified = false; // ���\�ϥΧޯ�
    	} 
		else if (!hasNotified) 
		{
        	cout << name << " does not have enough MP for Time Stasis!\n";
        	hasNotified = true; // �]�w�����w�g��ܹL
    	}
	}

};

class Monster : public Character
{
public:
	Monster(int h, int po, int kn) : Character("", 0, h, po, kn, 0 ,0) {}
	void print() { cout << "Monster "; Character::print(); }
	int getHP() { return hp; } 
	void setHP(int hp) { this->hp = hp; } 
	int getAttack() { return power; }
	int getKnowledge() { return knowledge; }
	void beatMonster(int exp) { }
};

class Team
{
protected:
	int memberCount;
	Character* member[10];
public:
	Team();
	~Team();
	void addWarrior(string name, int lv);
	void addWizard(string name, int lv);
	void addTimeTraveler(string name, int lv); 
	void memberBeatMonster(string name, int exp);
	void print();
	void combat(Monster *m);
};

Team::Team()
{
	memberCount = 0;
	for(int i = 0; i < 10; i++)
		member[i] = nullptr;
}

Team::~Team()
{
	for(int i = 0; i < memberCount; i++)
		delete member[i];
}

void Team::addWarrior(string name, int lv)
{
	if(memberCount < 10)
	{
		member[memberCount] = new Warrior(name, lv);
		memberCount++;
	}
}

void Team::addWizard(string name, int lv)
{
	if(memberCount < 10)
	{
		member[memberCount] = new Wizard(name, lv);
		memberCount++;
	}
}

void Team::addTimeTraveler(string name, int lv) 
{
    if (memberCount < 10) 
	{
        member[memberCount] = new TimeTraveler(name, lv);
        memberCount++;
    }
}

void Team::memberBeatMonster(string name, int exp)
{
	for(int i = 0; i < memberCount; i++)
	{
		if(member[i]->getName() == name)
		{
			member[i]->beatMonster(exp);
			break;
		}
	}
}

void Team::print()
{
	for(int i = 0; i < memberCount; i++)
		member[i]->print();
}

void Team::combat(Monster* m)
{
    while (true) 
	{
        // ���~�������۪�����
        int activeMembers = 0;
        for (int i = 0; i < this->memberCount; i++) 
		{
            if (this->member[i]->getHP() > 0) 
			{
                activeMembers++;
            }
        }

        if (activeMembers == 0) // �p�G�Ҧ��������w���`
		{ 
            cout << "Lose\n";
            m->print();
            return;
        }

        int monsterAvgAtk = (m->getAttack() + m->getKnowledge()) / activeMembers;

        for (int i = 0; i < this->memberCount; i++) 
		{
            if (this->member[i]->getHP() > 0) 
			{
                int updatedHp = this->member[i]->getHP() - monsterAvgAtk;
                this->member[i]->setHP(max(0, updatedHp));
            }
        }

        // �ɪŮȦ�̨ϥΧޯ�
        for (int i = 0; i < this->memberCount; i++) 
		{
            if (dynamic_cast<TimeTraveler*>(this->member[i]) != nullptr) 
			{
                auto tt = dynamic_cast<TimeTraveler*>(this->member[i]);
                if (tt->getHP() > 0) 
				{
                    tt->timeRewind(member, memberCount); // �ϥ� Time Rewind ��_������ HP
                    
                    tt->timeAcceleration(member, memberCount); // �s�W�ɶ��[�t�\��

                    tt->timeStasis(); // �s�W�ᵲ�ɶ��\��
                }
            }
        }

        // ������������~
        int sumAtk = 0;
        for (int i = 0; i < this->memberCount; i++) 
		{
            if (this->member[i]->getHP() > 0) 
			{
                sumAtk += this->member[i]->getAttack();
            }
        }
        m->setHP(m->getHP() - sumAtk);

        if (m->getHP() <= 0) // ���~���`
		{ 
            cout << "Win\n";
            this->print();
            return;
        }
        for (int i = 0; i < this->memberCount; i++) 
		{
            if (dynamic_cast<TimeTraveler*>(this->member[i]) != nullptr) 
			{
                auto tt = dynamic_cast<TimeTraveler*>(this->member[i]);
            }
        }
    }
}


int main()
{
	int mHP, mPower, mKnowledge;

	cin >> mHP >> mPower >> mKnowledge; // ��J���~��HP�Bpower�Bknowledge
	Monster mon(mHP, mPower, mKnowledge);

        Team myTeam;
        string name;
        int lv=0, role=0, memberCount=0;

       while (true) 
	   {
    		cin >> name;
        	if (name == "END") break; // ����r "END" ���ܵ�����J

        	cin >> lv >> role;
        	if (role == 1) 
			{
            	myTeam.addWarrior(name, lv); // �W�[�Ԥh
        	} 
			else if (role == 2) 
			{
            	myTeam.addWizard(name, lv); // �W�[�Ův
        	} 
			else if (role == 3) 
			{
            	myTeam.addTimeTraveler(name, lv); // �W�[�ɪŮȦ��
        	}
    	}
        myTeam.combat(&mon); // �i��԰��æC�L���G

        return 0;
		
}