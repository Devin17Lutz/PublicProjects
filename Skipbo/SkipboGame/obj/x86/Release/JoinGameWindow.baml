   M S B A M L   `   `   `  ���� E  ASkipboGame, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null'clr-namespace:SkipboGame
SkipboGame      SkipboGame.JoinGameWindow   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     *localclr-namespace:SkipboGame       � Title$  Join Skipbo Game��$	��270��$	��500�� � 
ResizeMode$ NoResize=� � WindowStartupLocation$ CenterScreen=�.��� 
��� � �.+��� $��Center=�.+��� $��Join a Skipbo Game��$��Center=�$��40(�$��0,0,0,20q�
��� ���� $��Center=�$��0,0,0,20q� � ColumnDefinitions �� $	��220 ��� $	��250 � � RowDefinitions �� $��50 ��� $��10 �.+��� $��30(�$��Game Sessions:��$��Right=�
��� ����� -    ��Name$ GameTagComboBox��$��2��$	��250�� �� SelectedIndex$ 0�� �� DisplayMemberPath$
 Name�� �� SelectedValuePath$
 Name��$��30(�$��Center=�
��� ������� *	GameTag+�� 	 �� Orientation$	 
Horizontal=�$��Center=�.+��� -   
 ��Name$
 
JoinButton��$��35(�$
��Join��$	��120��$��0,0,30,0q�
��� ����� -   $
 CancelButton��$��35(�$��Cancel��$	��120��
��� ���