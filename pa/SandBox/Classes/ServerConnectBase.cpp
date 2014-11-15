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

//送信
void ServerConnect::postData(){
    auto request = new HttpRequest();
    request->setUrl("https://api.parse.com/1/classes/acount");
    //api.parse.com/1/classes/SampleClass
    std::vector<std::string> key;
    key.push_back("X-Parse-Application-Id: o3xSqkK6aOvSvmkWmNABXWCTmNAkknxsCJEX8yMo");
    key.push_back("X-Parse-REST-API-Key: acHukv9BqnB7NIyFGhGiBqwNMo67UF7FW4XxIhpM");
    key.push_back("Content-Type: application/json");
    request->setHeaders(key);

    // POST送信
    request->setRequestType(HttpRequest::Type::POST);
    
    // 送りたいデータ(JSON形式)をセット
    auto data = "{\"acountId\":100, \"ColString\":\"ABC\"}";
    const char* buffer = data;
    request->setRequestData(buffer, strlen(buffer));
    
    // コールバック
    request->setResponseCallback(CC_CALLBACK_2(ServerConnect::postCallBackMethod, this));
    
    // リクエスト
    network::HttpClient::getInstance()->send(request);
    request->release();
}

void ServerConnect::postCallBackMethod(HttpClient* client, HttpResponse* response){
    if (response->isSucceed()) {
        //objectIdを取得
        std::vector<char> *buffer = response->getResponseData();
        
        char data[buffer->size()];
        for (int i = 0; i < buffer->size(); i++) {
            data[i] = buffer->at(i);
        }
        
        Json* json = Json_create(data);
        
        objectId = Json_getString(json, "objectId", "");
        log("Suceeded!　IDは%sです", objectId.c_str());
    }else{
        log("Failed");
    }
}

//受信
void ServerConnect::getData(){
    HttpRequest* request = new HttpRequest();
    request->setUrl("https://api.parse.com/1/classes/SampleClass/objectId");
    std::vector<std::string> key;
    key.push_back("X-Parse-Application-Id: o3xSqkK6aOvSvmkWmNABXWCTmNAkknxsCJEX8yMo");
    key.push_back("X-Parse-REST-API-Key: acHukv9BqnB7NIyFGhGiBqwNMo67UF7FW4XxIhpM");
    request->setHeaders(key);
    
    // GET送信
    request->setRequestType(HttpRequest::Type::GET);
    
    // callback
    request->setResponseCallback(CC_CALLBACK_2(ServerConnect::getCallBackMethod, this));
    
    // request
    HttpClient::getInstance()->send(request);
    request->release();
}

void ServerConnect::getCallBackMethod(HttpClient* client, HttpResponse* response){
    if (response->isSucceed()) {
        std::vector<char> *buffer = response->getResponseData();
        
        char data[buffer->size()];
        for (int i = 0; i < buffer->size(); i++) {
            data[i] = buffer->at(i);
        }
        
        Json* json = Json_create(data);
        
        //ColNum
        int dataNum = Json_getInt(json, "ColNum", 0);
        log("ColNumは%dです", dataNum);
        
        //ColString
        std::string dataString = Json_getString(json, "ColString", "");
        log("ColStringは%sです", dataString.c_str());
    }else{
        log("Failed");
    }
}