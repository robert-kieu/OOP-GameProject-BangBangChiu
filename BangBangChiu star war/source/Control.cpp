#include "Control.h"

int level = 1;
bool is_quit = false;
bool resume = false;
bool newGame = false;


bool ControlFunc::Init()	// Khoi tao che do su dung thu vien SDL voi kieu la: SDL_INIT_EVEYTHNG
{														
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);		// Thiet lap che do dinh dang video SDL trong windows.

	if (g_screen == NULL)
		return false;
	   
	//==================Font==================
	TextObject::InitFont();
	AudioFunction::prepareAudioFile();										// khoi tao file audio

	return true;
}



bool ControlFunc::prepareGame()
{
	bool isSuccess = true;
	bool ret;
	ret = BackgroundFunc::prepareBackground(level);							// load background theo man
	if (ret == 0)	isSuccess = false;	
	
	HpFunc::prepareHpMain();												// khoi tao HP cua main
	
	ret = HpFunc::prepareMainHpBorder();									// load thanh mau cua main
	if (ret == 0)	isSuccess = false;
	
	HpFunc::prepareHpBoss();												// khoi tao HP cua Boss

	ret = HpFunc::prepareBossHpBorder();									// load thanh mau cua Boss
	if (ret == 0)	isSuccess = false;

	ret = MainFunc::prepareMain();											// khoi tao MainObject
	if (ret == 0)	isSuccess = false;

	ThreatFunc::prepareThreats();											// khoi tao list Threat
	
	ret = ExplosionFunc::prepareExpSub();									// khoi vao vu no cua threat
	if (ret == 0)	isSuccess = false;
	ret = ExplosionFunc::prepareExpMain();									// khoi tao vu no cua main
	if (ret == 0)	isSuccess = false;

	GiftFunc::prepareGiftRocket();											// khoi tao Gift
	GiftFunc::prepareGiftHP();						
	GiftFunc::prepareGiftUpgrade();
	

	return isSuccess;
}

void ControlFunc::setup(const int &lv)				// khoi tao cac gia tri ban dau
{
	
	
	// khoi tao bien background:
	bkgn_x = 0;
	is_run_screen = true;
	
	g_bkground = NULL;
	
	// khoi tao bien trong control:
	level = lv;
	is_quit = false;
	resume = false;
	newGame = false;

	// khoi tao bien Gift:
	create = true;
	num_rocket = 0;
	num_blood = 0;
	time_of_lv2 = 0;

	// khoi tao bien HP:
	die_num = 0;
	die_num_boss = 0;
	DAME_OF_MAIN = 1;

	// khoi tao bien Menu:
	g_img_menu = NULL;
	TTF_Font* g_font_Menu = NULL;
	
	
	// khoi tao bien ThreatObject:
	activeBoss = false;
	activeSubBoss = false;
	listThreats.clear();
	listSub.clear();
	listSub.resize(2);

	mainObject.setXY_Val(0, 0);
	mainObject.setType(MainObject::LEVEL_1);
	g_event.type = SDL_NOEVENT;
}



int ControlFunc::playCampaign()
{
	//Bien luu diem: 
	//unsigned int score = 0;

	/*Score score;*/
	score.inputHighScoreFromFile();

	int type = 1;
	if(resume) loadGame(type, level, score);
	
	
	if (newGame) score.setScore(0);


	// Trong luc play game:
	while (!is_quit)
	{
		if (SDL_PollEvent(&g_event))//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			mainObject.handleInput(g_event, num_rocket, num_blood, DAME_OF_MAIN);
		}



		if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_s)
		{
			int catchMess = ::MessageBox(hWnd, "Do you want to save game?", "Save Game", MB_YESNO);
			switch (catchMess)
			{
			case IDYES:
				saveGame(type, level, score);
			case IDNO:
				break;
			default:
				break;
			}
			//if (MessageBox(NULL, "Do you want to save game?", "Game over", MB_OK) == IDOK) {
			//	saveGame(type, level, score);
			//	//return 1;
			//}
		}


		if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_ESCAPE)
		{
			int catchMess = ::MessageBox(hWnd, "Do you want to back to Menu?", "Pause", MB_YESNO);
			switch (catchMess)
			{
			case IDYES:
				return 1;
			case IDNO:
				break;
			default:
				break;
			}
		}

		// cap nhat lai background:
		if (is_run_screen == true)
		{

			bkgn_x -= SPEED_BACKGROUND;
			if (bkgn_x <= -(WIDTH_LONG_BACKGROUND - SCREEN_WIDTH))
			{
				is_run_screen = false;
				activeBoss = true;
			}
			else {
				SDLCommonFunc::applySurface(g_bkground, g_screen, bkgn_x, 0);
				SDLCommonFunc::applySurface(hp_border, g_screen, X_POS_HP_BORDER_MAIN, Y_POS_HP_BORDER_MAIN);
			}
		}
		else
		{
			SDLCommonFunc::applySurface(g_bkground, g_screen, bkgn_x, 0);
			SDLCommonFunc::applySurface(hp_border, g_screen, X_POS_HP_BORDER_MAIN, Y_POS_HP_BORDER_MAIN);
		}

		if (is_run_screen == false)
		{
			destroyThreatObjects(listThreats);
		}







		// --------------------------- THEM GIFT ---------------------------

	// Tao Gift rocket
		if (create && rand() % DELTA_DROP_ROCKET == 0) {
			gift_rocket->setIsMove(true);
			gift_rocket->setType(Gift::UPGRADE_AMO);
			gift_rocket->setRect(rand() % DELTA_DROP_ROCKET, rand() % (SCREEN_HEIGHT - gift_rocket->getRect().h));
			create = false;
		}
		if (gift_rocket->getIsMove()) {
			gift_rocket->showObject(g_screen);
			gift_rocket->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		else
			create = true;

		// Tao Gift hp
		if (create && rand() % DELTA_DROP_HP == 0) {
			gift_hp->setIsMove(true);
			gift_hp->setType(Gift::HP);
			gift_hp->setRect(rand() % DELTA_DROP_HP, rand() % (SCREEN_HEIGHT - gift_hp->getRect().h));
			create = false;
		}
		if (gift_hp->getIsMove()) {
			gift_hp->showObject(g_screen);
			gift_hp->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		else create = true;


	// Tao Gift upgrade máy bay
	if (create && rand() % DELTA_DROP_UPGRADE == 0) {
		gift_upgr_main->setIsMove(true);
		gift_upgr_main->setType(Gift::UPGRADE_SPACESHIP);
		gift_upgr_main->setRect(rand() % DELTA_DROP_UPGRADE, rand() % (SCREEN_HEIGHT - gift_upgr_main->getRect().h));
		create = false;
	}
	if (gift_upgr_main->getIsMove()) {
		gift_upgr_main->showObject(g_screen);
		gift_upgr_main->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	else create = true;
	//==============================================================

		bool ret;

		// hiệu ứng ăn item rocket
		if (SDLCommonFunc::checkCollision(mainObject.getRect(), gift_rocket->getRect())) {
			//this for main
			ExplosionObject main_eat_item;

			// ăn item được rocket
			num_rocket++;
			if (num_rocket > NUM_ROCKET) num_rocket--;
			ret = main_eat_item.loadImgObject("./image/eat_item.png");


			main_eat_item.set_clip_eat_item();
			if (!ret) return 0;

			for (int ex = 0; ex < 4; ex++) {

				int x_explo = (mainObject.getRect().x + mainObject.getRect().w * 0.5) - EXP_WIDTH * 0.5;
				int y_explo = (mainObject.getRect().y + mainObject.getRect().h * 0.5) - EXP_HEIGHT * 0.5;

				//upload explosion
				main_eat_item.set_frame(ex);
				main_eat_item.setRect(x_explo, y_explo);
				main_eat_item.showEx(g_screen);
				//update screen
				if (SDL_Flip(g_screen) == -1) return 0;
			}
			gift_rocket->setRect(rand() % GIFT_HP_WIDTH + SCREEN_WIDTH + DELTA_DROP_ROCKET, rand() % (SCREEN_HEIGHT - GIFT_HEIGHT));

		}




		// hiệu ứng ăn item hp
		if (SDLCommonFunc::checkCollision(mainObject.getRect(), gift_hp->getRect())) {
			//this for main
			ExplosionObject main_eat_item;

			// ăn quà hồi máu
			die_num = 0;
			hp.init();
			hp.render(g_screen);
			ret = main_eat_item.loadImgObject("./image/exp_main.png");

			main_eat_item.set_clip_small();
			if (!ret) return 0;

			for (int ex = 0; ex < 4; ex++) {

				int x_explo = (mainObject.getRect().x + mainObject.getRect().w * 0.5) - EXP_WIDTH * 0.5;
				int y_explo = (mainObject.getRect().y + mainObject.getRect().h * 0.5) - EXP_HEIGHT * 0.5;

				//upload explosion
				main_eat_item.set_frame(ex);
				main_eat_item.setRect(x_explo, y_explo);
				main_eat_item.showEx(g_screen);

				//update screen	
				if (SDL_Flip(g_screen) == -1) return 0;
			}
			gift_hp->setRect(rand() % GIFT_HP_WIDTH + SCREEN_WIDTH + DELTA_DROP_HP, rand() % (SCREEN_HEIGHT - GIFT_HP_HEIGHT));

		}


		// hiệu ứng ăn quà upgrade
		if (SDLCommonFunc::checkCollision(mainObject.getRect(), gift_upgr_main->getRect())) {
			//this for main
			ExplosionObject main_eat_item;

			bool ret = mainObject.loadImgObject("./image/main_lv2.png");				//main
			if (!ret)
			{
				return 0;
			}
			mainObject.setType(MainObject::LEVEL_2);
			mainObject.setWidthHeight(WIDTH_MAIN_OBJECT_LV2, HEIGHT_MAIN_OBJECT_LV2);

			// ăn item được rocket
			ret = main_eat_item.loadImgObject("./image/eat_item.png");


			main_eat_item.set_clip_eat_item();
			if (!ret) return 0;

			for (int ex = 0; ex < 4; ex++) {

				int x_explo = (mainObject.getRect().x + mainObject.getRect().w * 0.5) - EXP_WIDTH * 0.5;
				int y_explo = (mainObject.getRect().y + mainObject.getRect().h * 0.5) - EXP_HEIGHT * 0.5;

				//upload explosion
				main_eat_item.set_frame(ex);
				main_eat_item.setRect(x_explo, y_explo);
				main_eat_item.showEx(g_screen);
				//update screen
				if (SDL_Flip(g_screen) == -1) return 0;
			}
			gift_upgr_main->setRect(rand() % GIFT_UPGRADE_WIDTH + SCREEN_WIDTH + DELTA_DROP_UPGRADE, rand() % SCREEN_HEIGHT);

		}


		// check khi nào hết hạn lv2
		if (mainObject.getType() == MainObject::LEVEL_2) time_of_lv2++;
		if (time_of_lv2 == LIMIT_TIME_LV2) {
			time_of_lv2 = 0;
			bool ret = mainObject.loadImgObject("./image/main.png");				//main
			if (!ret)
			{
				return 0;
			}
			mainObject.setType(MainObject::LEVEL_1);
			mainObject.setWidthHeight(WIDTH_MAIN_OBJECT, HEIGHT_MAIN_OBJECT);
		}
		//+++++++++++++++++++++++++++++++++++++++++++++++




		// show hp
		hp.render(g_screen);


		// Implement main object:
		mainObject.handleMove();
		mainObject.showObject(g_screen);
		mainObject.makeAmo(g_screen);




		// nhieu threat:
		// có thẻ tao thành ham Move():
		for (int i = 0; i < listThreats.size(); i++)
		{

			// moi them 

			listThreats[i]->Move();


			// đạn của threat va chạm main
			vector<AmoObject*> amoList1 = listThreats[i]->GetAmoList();
			for (int k = 0; k < amoList1.size(); k++) {
				AmoObject* p_amo = amoList1.at(k);
				if (p_amo) {
					bool ret_col = SDLCommonFunc::checkCollision(p_amo->getRect(), mainObject.getRect());
					if (ret_col) {
						for (int ex = 0; ex < 4; ex++) {

							int x_explo = (p_amo->getRect().x);
							int y_explo = (p_amo->getRect().y);

							//upload explosion
							explo_main.set_frame(ex);
							explo_main.setRect(x_explo, y_explo);
							/*explo_main.showEx(g_screen);*/
							explo_main.showUpgrade(g_screen);

							//update screen
							if (SDL_Flip(g_screen) == -1) return 0;
						}

						// check hp
						die_num += DAME_OF_THREAT;
						if (mainObject.isDead()/*die_num >= LIFE*/) {
							Mix_PlayChannel(-1, g_sound_ex_main, 0);
							score.outHighScoreToFile(score.getScore());

							mainObject.setXY_Val(0, 0);
								return -1;
							//}
						}
						else {
							for (int i = 0; i < DAME_OF_THREAT; i++) hp.decreaseHP();
							hp.render(g_screen);
							if (SDL_Flip(g_screen) == -1) {

								//free memory
								//SDL_Quit();
								return 0;
							}
							// delete threat_amo when it collision main
							listThreats[i]->ResetAmo(p_amo);
						}//===============HP==================
					}
				}
			}
			//------------------------------------------------------------------------








			// Xu ly main va cham voi subBoss
			//check collision
			bool isColi = SDLCommonFunc::checkCollision(mainObject.getRect(), listThreats[i]->getRect());
			if (isColi) {
				/*score += 100;*/
				for (int ex = 0; ex < NUM_THREAT; ex++) {
					//main explosion animation
					int x_explo_main = (mainObject.getRect().x + mainObject.getRect().w * 0.5) - EXP_WIDTH * 0.5;
					int y_explo_main = (mainObject.getRect().y + mainObject.getRect().h * 0.5) - EXP_HEIGHT * 0.5;
					explo_main.set_frame(ex);
					explo_main.setRect(x_explo_main, y_explo_main);
					explo_main.showEx(g_screen);

					//threat explosion animation
					int x_explo_threat = (listThreats[i]->getRect().x + listThreats[i]->getRect().w * 0.5) - EXP_WIDTH * 0.5;
					int y_explo_threat = (listThreats[i]->getRect().y + listThreats[i]->getRect().h * 0.5) - EXP_HEIGHT * 0.5;

					//upload explosion
					exp_subboss.set_frame(ex);
					exp_subboss.setRect(x_explo_threat, y_explo_threat);
					exp_subboss.showEx(g_screen);

					//update screen
					if (SDL_Flip(g_screen) == -1) return 0;
				}

				// check hp
				die_num += DAME_COLLISION;
				if (mainObject.isDead()/*die_num >= LIFE*/) {
					Mix_PlayChannel(-1, g_sound_ex_main, 0);
					score.outHighScoreToFile(score.getScore());

					mainObject.setXY_Val(0, 0);
						return -1;
					//}
				}
				else {
					for (int i = 0; i < DAME_COLLISION; i++) hp.decreaseHP();
					hp.render(g_screen);
					if (SDL_Flip(g_screen) == -1) {
						//free memory
						//SDL_Quit();
						return 0;
					}
					listThreats[i]->Reset(SCREEN_WIDTH + i * 100 * 2);
				}//=========hp===========
			}









			//------------------------------------------------------------------------
			// Xu ly đạn cua Main vs Threat:
			vector<AmoObject*> amo_list = mainObject.getAmoList();
			for (int im = 0; im < amo_list.size(); im++)
			{
				AmoObject* p_amo = amo_list.at(im);
				if (p_amo != NULL)
				{
					bool ret_col = SDLCommonFunc::checkCollision(p_amo->getRect(), listThreats[i]->getRect());
					if (ret_col)
					{
						score.setScore(score.getScore() + 100);
						// Audio:

						Mix_PlayChannel(-1, g_sound_injured, 0);

						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (p_amo->getRect().x);
							int y_pos = (p_amo->getRect().y);

							exp_subboss.set_frame(ex);
							exp_subboss.setRect(x_pos, y_pos);
							exp_subboss.showExSmall(g_screen);

							if (SDL_Flip(g_screen) == -1)
								return 0;
						}

						int rng_y = rand() % SCREEN_HEIGHT;
						listThreats[i]->Reset(SCREEN_WIDTH + im * rng_y);
						if (p_amo->getType() != AmoObject::ROCKET) mainObject.removeAmo(im);
					}
				}
			}
		}





		// kich hoat boss:
		if (activeBoss)
		{
			pBoss->Move();
			pBoss->showObject(g_screen);
			pBoss->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
			activeSubBoss = true;
			SDLCommonFunc::applySurface(hp_border_boss, g_screen, X_POS_HP_BORDER_BOSS, Y_POS_HP_BORDER_BOSS);
			hp_boss.render_boss(g_screen);
		}







		// xu ly Sub Boss:
		if (activeSubBoss)
		{
			for (int i = 0; i < listSub.size(); i++)
			{
				listSub[i]->HandleMoveSub(pBoss);
				listSub[i]->showObject(g_screen);
				listSub[i]->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

				//-------------------------------------------------------------------------   draft:
				MainObject* pMain = &mainObject;





				//main vs đạn subboss ở cuối trận	   
				vector<AmoObject*> amoList2 = listSub[i]->GetAmoList();
				for (int k = 0; k < amoList2.size(); k++) {
					AmoObject* p_amo = amoList2.at(k);
					if (p_amo) {
						bool ret_col = SDLCommonFunc::checkCollision(p_amo->getRect(), pMain->getRect());
						if (ret_col) {
							for (int ex = 0; ex < 4; ex++) {

								int x_explo = (p_amo->getRect().x);
								int y_explo = (p_amo->getRect().y);

								//upload explosion
								explo_main.set_frame(ex);
								explo_main.setRect(x_explo, y_explo);
								explo_main.showEx(g_screen);

								//update screen
								if (SDL_Flip(g_screen) == -1) return 0;
							}

							// check hp
							die_num += DAME_OF_THREAT;
							if (mainObject.isDead()/*die_num >= LIFE*/) {
								Mix_PlayChannel(-1, g_sound_ex_main, 0);
								score.outHighScoreToFile(score.getScore());

								mainObject.setXY_Val(0, 0);
								return -1;
							
							}
							else {
								for (int i = 0; i < DAME_OF_THREAT; i++) hp.decreaseHP();
								hp.render(g_screen);
								if (SDL_Flip(g_screen) == -1) {
									//free memory
									//SDL_Quit();
									return 0;
								}
								// delete threat_amo when it collision main
								listSub[i]->ResetAmo(p_amo);
							}//===============HP==================
						}
					}
				}




				//main vs đạn boss ở cuối trận	   
				vector<AmoObject*> amoList3 = pBoss->GetAmoList();
				for (int k = 0; k < amoList3.size(); k++) {
					AmoObject* p_amo = amoList3.at(k);
					if (p_amo) {
						bool ret_col = SDLCommonFunc::checkCollision(p_amo->getRect(), pMain->getRect());
						if (ret_col) {
							for (int ex = 0; ex < 4; ex++) {

								int x_explo = (p_amo->getRect().x);
								int y_explo = (p_amo->getRect().y);

								//upload explosion
								explo_main.set_frame(ex);
								explo_main.setRect(x_explo, y_explo);
								explo_main.showEx(g_screen);

								//update screen
								if (SDL_Flip(g_screen) == -1) return 0;
							}

							// check hp
							die_num += DAME_OF_BOSS;
							if (mainObject.isDead()/*die_num >= LIFE*/) {
								Mix_PlayChannel(-1, g_sound_ex_main, 0);
								score.outHighScoreToFile(score.getScore());

								mainObject.setXY_Val(0, 0);
									return -1;
								//}
							}
							else {
								for (int i = 0; i < DAME_OF_BOSS; i++) hp.decreaseHP();
								hp.render(g_screen);
								if (SDL_Flip(g_screen) == -1) {
									return 0;
								}
								// delete threat_amo when it collision main
								pBoss->ResetAmo(p_amo);
							}//===============HP==================
						}
					}
				}




				// Xu ly amo cua Main vs subBoss:
				vector<AmoObject*> amo_list = pMain->getAmoList();
				for (int im = 0; im < amo_list.size(); im++)
				{
					AmoObject* p_amo = amo_list.at(im);
					if (p_amo != NULL)
					{
						bool ret_col = SDLCommonFunc::checkCollision(p_amo->getRect(), listSub[i]->getRect());
						if (ret_col)
						{
							score.setScore(score.getScore() + 100);
							// moi them:

							Mix_PlayChannel(-1, g_sound_injured, 0);

							for (int ex = 0; ex < 4; ex++)
							{
								int x_pos = (p_amo->getRect().x);
								int y_pos = (p_amo->getRect().y);

								exp_subboss.set_frame(ex);
								exp_subboss.setRect(x_pos, y_pos);
								exp_subboss.showExSmall(g_screen);
								
								if (SDL_Flip(g_screen) == -1)
									return 0;
							}

							SDL_Rect tempRect = pBoss->getRect();
							listSub[i]->setRect(tempRect.x - tempRect.w / 5, tempRect.y + tempRect.h / 2);
							if (p_amo->getType() != AmoObject::ROCKET) pMain->removeAmo(im);
						}
					}
				}


				// Xu ly amo cua Main vs Boss:
				vector<AmoObject*> amo_list_2 = pMain->getAmoList();
				for (int im = 0; im < amo_list_2.size(); im++)
				{
					AmoObject* p_amo = amo_list_2.at(im);
					if (p_amo != NULL)
					{
						bool ret_col = SDLCommonFunc::checkCollision(p_amo->getRect(), pBoss->getRect());
						if (ret_col)
						{
							// moi them:
							die_num_boss += DAME_OF_MAIN;



							for (int ex = 0; ex < 4; ex++)
							{
								int x_pos = (p_amo->getRect().x);
								int y_pos = (p_amo->getRect().y);

								exp_subboss.set_frame(ex);
								exp_subboss.setRect(x_pos, y_pos);
								exp_subboss.showExSmall(g_screen);
							
								if (SDL_Flip(g_screen) == -1)
									return 0;
							}
							if (p_amo->getType() != AmoObject::ROCKET) pMain->removeAmo(im);

							if (die_num_boss >= LIFE_BOSS) {
								score.setScore(score.getScore() + 1000);
								Mix_PlayChannel(-1, g_sound_ex_boss, 0);
								score.outHighScoreToFile(score.getScore());
								mainObject.setXY_Val(0, 0);
									return 2;
								//}
							}
							else {
								for (int i = 0; i < DAME_OF_MAIN; i++) hp_boss.decreaseHP_BOSS();
								hp_boss.render_boss(g_screen);
								if (SDL_Flip(g_screen) == -1) {
							
									return 0;
								}
								Mix_PlayChannel(-1, g_sound_injured, 0);
							}//===============HP==================
						}
					}
				}

			}
		}
		//Hien thi mark_value len man hinh
		string str_score = to_string(score.getScore());
		string Scorestr("Score: ");
		Scorestr += str_score;
		TextObject scoregame;
		scoregame.setText(Scorestr);
		scoregame.setColor(TextObject::RED_COLOR);
		scoregame.setRect(600, 5);
		scoregame.CreateGameText(g_font_text, g_screen);
		
		if (SDL_Flip(g_screen) == -1) {
			return 0;
		}
	}
	return true;
}





void ControlFunc::endGame()
{

	for (int i = 0; i < listThreats.size(); i++)
	{
		delete listThreats[i];
	}

	for (int i = 0; i < listSub.size(); i++)
	{
		delete listSub[i];
	}
	delete pBoss;


	Mix_CloseAudio();												// giai phong SDL_mixer	
	SDLCommonFunc::cleanUp();
	SDL_Quit();
}