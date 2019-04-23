# WGLDownloadProvider
This is a file download tool

一、框架的特点：

1、断点续传下载：
常规的文件下载，比较多项目用到的都是图片下载，这种类型的文件下载由于单个文件的体积很小，即使下载失败，再重新下载也不碍事，
很多时候都可以不考虑断点下载的问题。

视频这种大文件则不能忽略上面这些问题，由于文件体积的增大，由量变产生的质变之后再使用上面的常规方式下载则会产生一系列风险。
首先是断点续传的问题，例如视频下载的过程中，如果由于网络或者服务端的一些原因而下载失败，这个时候在进行重新下载显然是不可取的，用户也难以接受。

2、分片持久化：
常规的文件下载，如图片，由于单个文件的体积很小，所以可以等图片下载完再一次性将其读取到内存中，也不会存在内存暴涨的风险。
但是视频这类型的大文件，显然一次性将文件读取到内存中是不可取的，会因为内存暴涨导致app有崩溃闪退的风险。
因此文件的分片持久化也就成了顺理成章的方案。

3、下载优先级：
目前支持两种下载优先级：
A、先进先出；B、后进先出

4、最大支持下载数：
默认-1，即不做限制，支持任意下载任务数

5、最大并发下载数：
默认并发下载数为2（当然，实际最大支持的下载并发数还是依赖CPU系统）

6、回调：
目前支持两种方式的回调：
A、block回调；B、delegate回调
（delegate回调的方式，内部通过一个 NSMutableDictionary <NSString *, WGLDownloadDelegate *> *taskDelegatesForUrl映射表来管理）


二、SDK的优化记录：

 1、SDK旧版本，存在一个弊端：
 
 文件下载的时候，因为考虑到大文件内存有暴涨的风险，所以选择了边下载边持久化本地磁盘的方案。但是这个方案带来另一个问题，就是一旦下载过程中，
 网络中断或者app进程被杀，导致下载被迫中止，这时候磁盘缓存的文件就是不完整。
 
 这会引起什么问题呢？
 
 因为SDK在下载前会先判断文件时候已存在，如果已经存在，则不会继续下载，避免同一个文件多次重复下载，浪费流量。
 如果通过SDK的缓存是否存在的接口判断，会认为缓存已存在，业务端可能就不再下载。
 导致与下载SDK的断点续传下载功能产生了冲突。
 
 2、修复方案：
 文件开始下载的时候，下载的文件（尚未下载完成的文件）会存放在一个临时目录self.tempDownloadDirectory中，只有等文件下载完成后，
 再将文件从临时目录迁移到指定的目录self.downloadDirectory。
 所以，如果缓存的文件不完整（未下载完成），SDK判断缓存是否存在，是通过判断指定目录self.downloadDirectory下是否有，
 因为只有文件下载完成了，指定目录下才会有缓存，所以这时候SDK就会进行断点续传下载（断点续传下载选择判断的目录是临时目录）。
 
 