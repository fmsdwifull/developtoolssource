<div class="page">
	<div class="pageContent">
		<form method="post" action="<?php echo CHtml::normalizeUrl(array('user/add'));?>" class="pageForm required-validate" onsubmit="return validateCallback(this, dialogAjaxDone)">
			<div class="pageFormContent" layoutH="58">
				<div class="unit">
					<label>账号：</label>
					<input type="text" class="required" size="30" maxlength="20" name="data[username]" />
				</div>
				<div class="divider"></div>

				<div class="unit">
					<label>密码：</label>
					<input type="password" name="data[password]" size="30" maxlength="20" class="required"/>
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