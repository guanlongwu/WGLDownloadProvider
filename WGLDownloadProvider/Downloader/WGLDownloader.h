//
//  WGLDownloader.h
//  WGLDownloadProvider
//
//  Created by wugl on 2018/12/21.
//  Copyright © 2018年 WGLKit. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WGLUtil.h"
@class WGLDownloaderInfo;
@protocol WGLDownloaderDataSource;
@protocol WGLDownloaderDelegate;

@interface WGLDownloader : NSObject

@property (nonatomic, weak) id <WGLDownloaderDataSource> dataSource;
@property (nonatomic, weak) id <WGLDownloaderDelegate> delegate;

/**
 下载地址url
 */
@property (nonatomic, copy) NSString *urlString;

/**
 下载范围
 */
@property (nonatomic, assign) uint64_t fromByte, toByte;

/**
 下载文件存放路径
 */
@property (nonatomic, readonly) NSString *downloadFilePath;

/**
 下载文件大小
 */
@property (nonatomic, readonly) uint64_t downloadFileSize;

/**
 下载状态
 */
@property (nonatomic, readonly) WGLDownloadState downloadState;

/**
 开始下载
 */
- (void)start;

/**
 取消下载
 */
- (void)cancel;


@end


@protocol WGLDownloaderDataSource <NSObject>

//文件下载的存放目录
- (NSString *)downloaderGetDirectory:(WGLDownloader *)downloader urlString:(NSString *)urlString;

//文件缓存的唯一key
- (NSString *)downloaderCacheFileName:(WGLDownloader *)downloader urlString:(NSString *)urlString;

@end


@protocol WGLDownloaderDelegate <NSObject>

//下载开始
- (void)downloadDidStart:(WGLDownloader *)downloader;

//下载中
- (void)downloader:(WGLDownloader *)downloader didReceiveLength:(uint64_t)receiveLength totalLength:(uint64_t)totalLength;

//下载成功
- (void)downloadDidFinish:(WGLDownloader *)downloader filePath:(NSString *)filePath;

//下载失败
- (void)downloadDidFail:(WGLDownloader *)downloader errorType:(WGLDownloadErrorType)errorType;

@end



