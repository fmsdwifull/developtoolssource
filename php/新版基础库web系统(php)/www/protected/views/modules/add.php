<div class="page">
	<div class="pageContent">
		<form method="post" action="<?php echo CHtml::normalizeUrl(array('modules/add'));?>" enctype="multipart/form-data" onsubmit="return iframeCallback(this, dialogAjaxDone);">
			<div class="pageFormContent" layoutH="58">
				<div class="unit">
					<label>模块名称：</label>
					<input type="text" class="required" size="50" name="data[module_name]" />
				</div>
				<div class="divider"></div>

				<div class="unit">
					<label>模块的类型：</label>
					<select name="data[type]">
						<option value="0">内存</option>
						<option value="1">字符串</option>
						<option value="2">网络</option>
						<option value="3">数据结构</option>
					</select>
				</div>
				<div class="divider"></div>

				<div class="unit">
					<label>模块描述：</label>
					<textarea name="data[desciption]" cols="50" rows="3" class="textInput required"></textarea>
				</div>
				<div class="divider"></div>
				
				<div class="unit">
					<label>注意事项：</label>
					<textarea name="data[remarks]" cols="50" rows="3" class="textInput"></textarea>
				</div>
				<div class="divider"></div>

				<div class="unit">
					<label>需要引用的头文件：</label>
					<input type="text" size="50" name="data[requirements]" />
				</div>
				<div class="divider"></div>
				
				<div class="unit">
					<label>文件路径名：</label>
					<input type="file" size="26" name="Modules[link]"/>
				</div>
				<div class="divider"></div>
				
				<div class="unit">
					<label>负责人：</label>
					<input type="text" size="50" name="data[supporter]" class="required"/>
				</div>
				<div class="divider"></div>
				
				<div class="unit">
					<label>是否启用：</label>
					<select name="data[enabled]">
						<option value="1">是</option>
						<option value="0">否</option>
					</select>
				</div>
				<div class="divider"></div>
				
			</div>
			<div class="formBar">
				<ul>
					<li><div class="buttonActive"><div class="buttonContent"><button type="submit">提交</button></div></div></li>
					<li><div class="button"><div class="buttonContent"><button type="button" class="close">取消</button></div></div></li>
				</ul>
			</div>
		</form>
	</div>
</div>