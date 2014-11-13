//
//  ServerConnectBase.cpp
//  SandBox
//
//  Created by Park Station on 2014. 11. 11..
//
//

#include "ServerConnectBase.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"
#include "spine/Json.h"

using namespace cocos2d::network;

USING_NS_CC;

ServerConnect::ServerConnect(){
}
ServerConnect::~ServerConnect(){
}

void ServerConnect::requestData(){
    auto request = new HttpRequest();
    request->setUrl("https://api.parse.com/1/classes/SampleClass");
    //api.parse.com/1/classes/SampleClass
    std::vector<std::string> key;
    key.push_back("X-Parse-Application-Id: o3xSqkK6aOvSvmkWmNABXWCTmNAkknxsCJEX8yMo");
    key.push_back("X-Parse-REST-API-Key: acHukv9BqnB7NIyFGhGiBqwNMo67UF7FW4XxIhpM");
    key.push_back("Content-Type: application/json");
    request->setHeaders(key);
    //https://www.parse.com/apps/parkpark/collections#class/SampleClass
    // POST送信
    request->setRequestType(HttpRequest::Type::POST);
    
    // 送りたいデータ(JSON形式)をセット
    auto data = "{\"ColNum\":100, \"ColString\":\"ABC\"}";
    const char* buffer = data;
    request->setRequestData(buffer, strlen(buffer));
    
    // コールバック
    request->setResponseCallback(CC_CALLBACK_2(ServerConnect::callbackFunc, this));
    
    // リクエスト
    network::HttpClient::getInstance()->send(request);
    request->release();
}

void ServerConnect::callbackFunc(HttpClient* client, HttpResponse* response){
    if (response->isSucceed()) {
        //objectIdを取得
        std::vector<char> *buffer = response->getResponseData();
        
        char data[buffer->size()];
        for (int i = 0; i < buffer->size(); i++) {
            data[i] = buffer->at(i);
        }
        
        Json* json = Json_create(data);
        
        std::string objectId = Json_getString(json, "objectId", "");
        log("Suceeded!　IDは%sです", objectId.c_str());
    }else{
        log("Failed");
    }
}