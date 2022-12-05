#include "GameScene.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

GameScene::~GameScene()
{
	delete spriteBG;
	for (Object3d* object : object3d) { delete object; }
	delete model;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	// 3Dオブジェクト生成
	model->Initialize();
	model->Create();

	for (size_t i = 0; i < 2; i++)
	{
		object3d.push_back({});
		object3d[i] = Object3d::Create();
		object3d[i]->SetModel(model);
		object3d[i]->Update();
	}

	sphere = { {0,2,0},1.0f };
	plane = { {0,1,0},0 };
	triangle.p[0] = { -1,0,-1 };
	triangle.p[1] = { -1,0,1 };
	triangle.p[2] = { 1,0,-1 };
	triangle.normal = { 0,1,0 };
	ray.start = { 0,1,0 };
	ray.dir = { 0,-1,0 };
}

void GameScene::Update()
{
	float moveSpd = 0.01f;

	ray.start +=
	{
		(input->PushKey(DIK_RIGHT) - input->PushKey(DIK_LEFT))* moveSpd,
			(input->PushKey(DIK_UP) - input->PushKey(DIK_DOWN))* moveSpd,
			0
	};

	std::ostringstream raystr;
	raystr << "ray.start:("
		<< std::fixed << std::setprecision(2)
		<< ray.start.x << ","
		<< ray.start.y << ","
		<< ray.start.z << ")";

	debugText.Print(raystr.str(), 50, 180, 1.0f);

	Vector3 inter;
	float distance;
	if (Collision::CheckRay2Plane(ray, plane, &distance,&inter))
	{
		debugText.Print("HIT", 50, 200, 1.0f);

		raystr.str("");
		raystr.clear();
		raystr << "("
			<< std::fixed << std::setprecision(2)
			<< inter.x << ","
			<< inter.y << ","
			<< inter.z << ")";
		debugText.Print(raystr.str(), 50, 220, 1.0f);
	}

	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
	}

	for (Object3d* object : object3d) { object->Update(); }
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	//for (Object3d* object : object3d) { object->Draw(); }

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
