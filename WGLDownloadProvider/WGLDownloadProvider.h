//
//  WGLDownloadProvider.h
//  WGLKit
//
//  Created by wugl on 2018/12/17.
//  Copyright © 2018年 WGLKit. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WGLUtil.h"
@protocol WGLDownloadProviderDataSource;
@protocol WGLDownloadProviderDelegate;

typedef NS_ENUM(NSInteger, WGLDownloadExeOrder) {
    // 以队列的方式，按照先进先出的顺序下载。这是默认的下载顺序
    WGLDownloadExeOrderFIFO,
    // 以栈的方式，按照后进先出的顺序下载。（以添加操作依赖的方式实现）
    WGLDownloadExeOrderLIFO
};

@interface WGLDownloadProvider : NSObject

@property (nonatomic, weak) id <WGLDownloadProviderDataSource> dataSource;
@property (nonatomic, weak) id <WGLDownloadProviderDelegate> delegate;

/**
 最大支持下载数
 默认-1，表示不进行限制
 */
@property (nonatomic, assign) NSInteger maxDownloadCount;

/**
 最大并发下载数
 默认2
 */
@property (nonatomic, assign) NSInteger maxConcurrentDownloadCount;

/**
 下载优先级
 默认先进先出
 */
@property (nonatomic, assign) WGLDownloadExeOrder executeOrder;

//下载入口
- (void)downloadWithURL:(NSString *)urlString;

@end


@protocol WGLDownloadProviderDataSource <NSObject>

//是否已缓存
- (BOOL)downloadProvider:(WGLDownloadProvider *)dlProvider existCache:(NSString *)urlString;

@end


@protocol WGLDownloadProviderDelegate <NSObject>

//下载开始
- (void)downloadDidStart:(WGLDownloadProvider *)dlProvider;

//下载中
- (void)downloader:(WGLDownloadProvider *)dlProvider didReceiveLength:(uint64_t)receiveLength totalLength:(uint64_t)totalLength;

//下载成功
- (void)downloadDidFinish:(WGLDownloadProvider *)dlProvider filePath:(NSString *)filePath;

//下载失败
- (void)downloadDidFail:(WGLDownloadProvider *)dlProvider errorType:(WGLDownloadErrorType)errorType;

@end
