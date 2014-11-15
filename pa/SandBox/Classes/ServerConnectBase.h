//
//  ServerConnectBase.h
//  SandBox
//
//  Created by Park Station on 2014. 11. 11..
//
//

#ifndef __SandBox__ServerConnectBase__
#define __SandBox__ServerConnectBase__
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"
#include <cocos2d.h>
#include <stdio.h>
#include <spine/Json.h>
//class ServerConnect : public cocos2d::Node{
class ServerConnect{
    public:
    std::string objectId;
    ServerConnect();
    virtual ~ServerConnect();
    void postData();
    void getData();
    void postCallBackMethod(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
    void getCallBackMethod(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
};

#endif /* defined(__SandBox__ServerConnectBase__) */
