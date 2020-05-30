# Unity Shader Intro

``` c#
// unity shader lab template
Shader “name”{
	Properties{
		// 定义属性，可以在属性查看器显示
		_MainTex ("Base (RGB)", 2D) = "white" {}
		// name(“display name”, type) = default_value {option}

		// 1. nums & sliders: _Int, _Float, _Range
		// 2. vectors & color: _Color, _Vector
		// 3. textures: _2D, _3D, _Cube
		}


	Category{
			SubShader
		{
			// 子着色器列表
		
		Tags{
			// 标签
			"RenderType"="Opaque"
			// "key"="value"
		}
		
		
		CommonState
		// 通用状态

		Pass{
				CGPROGRAM				// cg script begin
				#pragma surface surf Lambert addshadow	//表面着色器
				// #pragma surface 入口函数名称 光照模型 [options]
			    #pragma shader_feature REDIFY_ON

			    void surf(Input IN, inout SurfaceOutput o) 
			    {
			    	blahblah
			    	// return xxx 流给下一个流水线模块
			    }
			    // 顶点片元着色器
			    // #pragma vertex [name] 顶点着色器
			    // float4 [name](float4 input: POTISION):POTISION
			    // { return xxxx }
			    // #pragma fragment [name] 片元着色器
			    // fixed4 [name]():COLOR { return fixed4(a,b,c,d)}
				ENDCG  					//cg script end
		}

		// Pass{[Name and Tags][RenderSetup][TextureSetup]}
		// 通道列表
		// 1. RegularPass 通用设置，光照、纹理、雾等 
		// 2. UsePass 插入其他着色器
		// 3. GrabPass{"Name"} 捕获物理所在位置的屏幕内容（截屏），写入纹理中，并进行后续通道操作。使用_GrabTexture访问
	
	}
	Fallback "Name"
	// 子着色器显卡不支持的情况下，降级为fallback
}
```



## 坐标空间

1. 物体空间： 几何体中心为原点，人物以双脚为原点（相对坐标系？）
2. 世界空间： （绝对坐标系？）
3. 摄像机空间： 观察摄像机为原点
4. 投影成像： 3D坐标—>屏幕空间



## 常见矩阵

1. UNITY_MATRIX_M 基本矩阵
2. UNITY_MATRIX_P 投影矩阵
3. UNITY_MATRIX_V 摄像机矩阵
4. UNITY_MATRIX_T_MV (基本矩阵x摄像机矩阵)转置
5. UNITY_MATRIX_IT_MV (基本矩阵x摄像机矩阵)逆转置
6. UNITY_MATRIX_TEXTURE0 纹理变化矩阵



## 管道流水线



## 顶点片元着色器

常见语义修饰

1. POSITION
2. TANGENT 切线
3. NORMAL 法线
4. TEXCOORD0 第一套纹理
5. TEXCOORD1
6. TEXCOORD2
7. TEXCOORD3
8. COLOR 颜色



基本类型表达式（部分）

1. fixed 定点数
2. sampler* 纹理对象句柄 1D/2D/3D/CUBE/RECT
3. Float4 向量数据类型
4. float1*1, float2*3…float4*4 内置矩阵数据类型
5. 语义绑定 float4 a:POSITION



入口函数：输入输出语义（不同管道接口之间的通用有意义的参数）



`UnityCG.cginc` unity自带函数库



## 表面着色器

顶点变换函数/表面着色函数/光照模型/最终颜色修改函数—>顶点着色器

表面着色函数

```c#
#pragma surface 入口函数名称 光照模型 [options]
void surf (Input IN, inout SurfaceOutput o) {}
```

光照模型：Lambert(漫反射光照)/ BlinnPhong(高光反射)/ 自定义光照

``` c#
[options]

// vertex入口函数

Vertex:name
Void <name>(inout appdata_full v) // 修改顶点着色器输入坐标
Half4 <name>(inout appdata_full v, out Input o) // 修改顶点着色器输入坐标，为表面着色器传递数据

// 最终颜色修改函数

finalcolor: name
Void <name>(Input IN, inout SurfaceOutput o, inout fixed4 color){}
```

## LOD与渲染路径

LOD(level of detail)根据不同情况设置maxinum_lod，调用不同的shader.