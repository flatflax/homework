#### todo
- [ ] 动态加载资源
- [ ] 状态机
- [ ] 热更新(Lua)

#### 参考手册：
* [官方文档](https://docs.unity3d.com/ScriptReference/index.html)

#### 部分方法参考
1. 脚本加载资源

```
audioSource.clip = Resources.Load<AudioClip>("prefabs/lv" + nationNum.ToString());
```

2. 脚本添加和删除控件
```
gameObject.GetComponent<Image>();
gameObject.AddComponent<Image>();

Image image = gameObject.GetComponent<Image>();
Destory(image);
```

3. 设置公有变量
```
PlayPrefs.SetInt(key, value);
PlayPrefs.GetInt(key);
PlayPrefs.DeleteKey(key);
```

4. 搜索gameObject
```
GameObject[] gameObjects = GameObject.FindGameObjectsWithTag("tag");

GameObject gameObject = FindObjectOfType<TypeName>();
```

5. 按键监听事件
```
m_YourFirstButton.onClick.AddListener(TaskOnClick);
m_YourSecondButton.onClick.AddListener(delegate {TaskWithParameters("Hello"); });
m_YourThirdButton.onClick.AddListener(() => ButtonClicked(42));
m_YourThirdButton.onClick.AddListener(TaskOnClick);
```

6. json

解析json
```
using UnityEngine;

InputData _inputData = new InputData();

InputData inputData
{
    get
    {
        return _inputData;
    }
    set
    {
        _inputData = value;
    }
}

private void LoadData(string json)
{
    if(json.length>0)
    {
    return JsonUtility.FromJson<InputData>(json);
    }
    return null;
}

private void GetJsonValue(InputData data)
{
    // get test value
    return data.test;
}

```
定义`InputData`
```
using UnityEngine;
using System;
using System.Collections;

[Serializable]
public class InputData
{
    public string test;
}
```

7. 实例化prefabs
```
GameObject.Instantiate(runningPrefabs);
```

#### 一些经验

- 资源加载

  * 异步加载场景、异步加载资源

    异步加载场景：Loading界面

    ```
    Application.LoadLevelAsync("yourScene");
    Application.LoadLevelAdditiveAsync ("yourScene");
    ```

    异步加载资源：主要界面下，不同状态的GameObject分别激活不同资源的情况下，可以考虑在初始化场景的时候再根据状态挂载对应的资源、监听事件等

  * prefabs、脚本内挂载

- ios下的应用唤醒

`SocialShare.mm`
```
#import "SocialShare.h"
#import <Social/Social.h>
#import <AssetsLibrary/AssetsLibrary.h>

NSString * const STR_SPLITTER = @"|";
NSString * const STR_EOF = @"endofline";
NSString * const STR_ARRAY_SPLITTER = @"%%%";

@interface SocialShare ()
{
    NSMutableArray *imageArray;//经过压缩的图片
    NSString* tempPath;
}
@property (nonatomic, strong) NSString *theMainPath;
@property (nonatomic, strong) NSString *theVideoName;
@end



@implementation GJCSocialShare

static GJCSocialShare * shared_Instance;

+ (id)sharedInstance {
    
    if (shared_Instance == nil)  {
        shared_Instance = [[self alloc] init];
    }
    
    return shared_Instance;
}

+ (void)PostShareImageToInstagram:(NSString*)imagePath
{
    NSLog(@"save video url: %@", imagePath);
    NSURL* instagramURL = [NSURL URLWithString:@"instagram://app"];
    if ([[UIApplication sharedApplication] canOpenURL:instagramURL]){
        NSString *caption = @"Some Preloaded Caption";
        ALAssetsLibrary *library = [[ALAssetsLibrary alloc] init];
        [library writeVideoAtPathToSavedPhotosAlbum:[NSURL URLWithString:imagePath] completionBlock:^(NSURL *assetURL, NSError *error) {
            NSString *escapedString   = [GJCSocialShare urlencodedString:[assetURL absoluteString]];
            NSString *escapedCaption  = [GJCSocialShare urlencodedString:caption];
            NSURL *insURL = [NSURL URLWithString:[NSString stringWithFormat:@"instagram://library?AssetPath=%@&InstagramCaption=%@", escapedString, escapedCaption]];
            [[UIApplication sharedApplication] openURL:insURL];
        }];
    }else{
        NSLog(@"无法打开Instagram，请确定是否安装了Instagram！");
//        UnitySendMessage("InstagramShare", "OnNativeShareUninstall", [GJC_DataConvertor NSStringToChar:@"instagram"]);
        NSString *itunesurl = @"itms-apps://itunes.apple.com/us/app/id389801252";
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:itunesurl]];
    }
}

+ (NSString*)urlencodedString:(NSString *)message{
    return [message stringByAddingPercentEncodingWithAllowedCharacters:[NSCharacterSet alphanumericCharacterSet]];
}

@end


@implementation GJC_DataConvertor


+(NSString *) charToNSString:(char *)value {
    if (value != NULL) {
        return [NSString stringWithUTF8String: value];
    } else {
        return [NSString stringWithUTF8String: ""];
    }
}

+(const char *)NSIntToChar:(NSInteger)value {
    NSString *tmp = [NSString stringWithFormat:@"%ld", (long)value];
    return [tmp UTF8String];
}

+ (const char *) NSStringToChar:(NSString *)value {
    return [value UTF8String];
}

+ (NSArray *)charToNSArray:(char *)value {
    NSString* strValue = [GJC_DataConvertor charToNSString:value];
    
    NSArray *array;
    if([strValue length] == 0) {
        array = [[NSArray alloc] init];
    } else {
        array = [strValue componentsSeparatedByString:STR_ARRAY_SPLITTER];
    }
    
    return array;
}

+ (const char *) NSStringsArrayToChar:(NSArray *) array {
    return [GJC_DataConvertor NSStringToChar:[GJC_DataConvertor serializeNSStringsArray:array]];
}

+ (NSString *) serializeNSStringsArray:(NSArray *) array {
    
    NSMutableString * data = [[NSMutableString alloc] init];
    
    
    for(NSString* str in array) {
        [data appendString:str];
        [data appendString: STR_ARRAY_SPLITTER];
    }
    
    [data appendString: STR_EOF];
    
    NSString *str = [data copy];
#if UNITY_VERSION < 500
    [str autorelease];
#endif
    
    return str;
}
+ (NSMutableString *)serializeErrorToNSString:(NSError *)error {
    NSString* description = @"";
    if(error.description != nil) {
        description = error.description;
    }
    
    return  [self serializeErrorWithDataToNSString:description code: (int) error.code];
}
+ (NSMutableString *)serializeErrorWithDataToNSString:(NSString *)description code:(int)code {
    NSMutableString * data = [[NSMutableString alloc] init];
    
    [data appendFormat:@"%i", code];
    [data appendString: STR_SPLITTER];
    [data appendString: description];
    
    return  data;
}
+ (const char *) serializeErrorWithData:(NSString *)description code: (int) code {
    NSString *str = [GJC_DataConvertor serializeErrorWithDataToNSString:description code:code];
    return [GJC_DataConvertor NSStringToChar:str];
}
+ (const char *) serializeError:(NSError *)error  {
    NSString *str = [GJC_DataConvertor serializeErrorToNSString:error];
    return [GJC_DataConvertor NSStringToChar:str];
}
@end


extern "C" {
    void _TS_ShareImageWithInstagram(char* path) {
        NSString *savePath = [GJC_DataConvertor charToNSString:path];
        [GJCSocialShare PostShareImageToInstagram:savePath];
    }
}

```

根据url，判断是否有ins，如果没有则跳转到应用商店。
如果有ins，则将给定图片拼接url分享

- 滚动条`ScrollRect`

  控件内设定相关的`content`和`viewport`。

      - 搭配`contentSizeFitter`使用，
  - 搭配`Vertical Layout Group`或者`Horizon Layout Group`使用

* `todo`热更新

由于C#下实现热更新比较麻烦，通常使用Lua实现热更新的功能