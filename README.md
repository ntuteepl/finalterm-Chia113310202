[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/_v8RbUGg)

輸入 : 生命值 >> 攻擊力 >> 知識
      姓名 >> 等級 >> 角色
      (當輸入END表示人物輸入結束)  

輸出 : 剛剛使用的時間技能
      Win / Lose
      [角色] [姓名] : [等級] ( [經驗值] / [升級所需經驗值] )，[生命值] [攻擊] [知識] [幸運值] [魔力]

範例1 : 輸入 100 20 10
             Alice 5 1
             Bob 4 2
             Cathy 3 3
             END
        輸出
             Cathy used Time Rewind! The team recovered HP.   
             Cathy used Time Acceleration! Team gains double EXP next round.   
             Cathy used Time Stasis! Monster skips its attack this round.   
             Win
             Warrior Alice: 5 (1700/2500), 520-50-25-25-0
             Wizard Bob: 4 (1000/1600), 340-16-60-28-200
             TimeTraveler Cathy: 3 (500/900), 260-15-45-15-0

範例2 : 輸入 1000 80 50
             Alice 3 1
             Bob 2 2
             Cathy 4 3
             END
        輸出
             Cathy used Time Rewind! The team recovered HP.   
             Cathy used Time Acceleration! Team gains double EXP next round.   
             Cathy used Time Stasis! Monster skips its attack this round.   
             Cathy used Time Rewind! The team recovered HP. 
             Cathy does not have enough MP for Time Acceleration! 
             Cathy does not have enough MP for Time Stasis!
             Cathy does not have enough MP for Time Rewind!
             Lose
             Monster : 0 (100/0), 220-80-50-0-0



           
