   M S B A M L   `   `   `  ���� E  ASkipboGame, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null'clr-namespace:SkipboGame
SkipboGame  !    SkipboGame.CreateGameWindow   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     *localclr-namespace:SkipboGame       � Title$  Create Skipbo Game��$	��325��$	��500�� � 
ResizeMode$ NoResize=� � WindowStartupLocation$ CenterScreen=�.��� 
��� � �.+��� $��Center=�.+��� $��Create Your Skipbo Game��$��Center=�$��40(�$��0,0,0,20q�
��� ���� $��Center=�$��0,0,0,20q� � ColumnDefinitions �� $	��160 ��� $	��250 � � RowDefinitions �� $��50 ��� $��10 ��� $��50 �.+��� $��30(�$��	Game Tag:��$��Right=�
��� ����� $��4��$��30(�$��# of Decks:��$��Right=�
��� ����� -    ��Name$ GameTagTextBox��$��1��$��35(�
��� ����� -    ��Name$ DeckComboBox��$��4��$��2��$��50�� �� SelectedIndex$ 1��$��30(�$��Center=�
��� ���
��� ���.@��� $��1��$��Center=�$��Center=�
��� � �
��� ���$��50���� $��2��$��Center=�$��Center=�
��� � �
��� ���$��50���� $��3��$��Center=�$��Center=�
��� � �
��� ���$��50����  �� Orientation$ 
Horizontal=�$��Center=�.+��� -   	 ��Name$	 CreateButton��$��35(�$��Create��$��0,0,30,0q�
��� ����� -   $	 CancelButton��$��35(�$��Cancel��
��� ���